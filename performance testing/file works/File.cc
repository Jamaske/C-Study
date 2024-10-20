#include <stdexcept>
#include "File.h"


#ifdef __linux__

File::Handle::Handle() :file(0), size(0), state(State::close) {}
File::Handle::~Handle() { close(); }

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> 

void File::Handle::init(State new_mode, const char* name) {
    close();
    int flag = O_LARGEFILE;
    switch (new_mode) {
    case State::read:  flag |= O_RDONLY; break;
    case State::write: flag |= O_WRONLY | O_CREAT | O_TRUNC; break;
    case State::both:  flag |= O_RDWR | O_CREAT; break;
    case State::append:flag |= O_WRONLY | O_CREAT | O_APPEND; break;
    default: return;
    }

    file = (intptr_t)::open(name, flag, S_IRUSR | S_IWUSR);
    if (file == -1) throw std::runtime_error("Failed to open file");
    state = new_mode;

    struct stat prop;
    if (fstat((int)file, &prop)) throw std::runtime_error("Cant access file propertys");
    size = prop.st_size;
}

void File::Handle::close() {
    if (isOpen()) {
        state = State::close;
        ::close((int)fileHandle);
    }
}

inline bool File::Handle::isOpen() {
    return state != State::close;
}

File::Buffer::Buffer() : data(nullptr), size(0ull) {

}

File::Buffer::~Buffer() {

}


void File::Buffer::set(Provision new_provision, size_t req_size, intptr_t arg) {
    if (new_provision == provision && size >= req_size) return;
    free();
    switch (new_provision) {
    case Provision::stack: data = (char*)arg; break;//arg is stack buffer pointer
    case Provision::malloc: data = reinterpret_cast<char*>(malloc(req_size)); break;
    case Provision::maped:
        if (arg == -1) {
            data = mmap(nullptr, req_size, )//arg is a file descriptor
        }

    }
    size = req_size;
    provision = new_provision;
}

void File::Buffer::alloc(size_t req_size) {
    if (provision == Provision::malloc && size >= req_size) return;
    free();
    data = reinterpret_cast<char*>(malloc(req_size));
    if (!data) throw std::bad_alloc();
    size = req_size;
    provision = Provision::malloc;
}

void File::Buffer::map(size_t req_size, int fd) {
}

inline void File::Buffer::free() {
    if (!data) return;
    switch (provision) {
    case Provision::stack: break;
    case Provision::malloc: free(data); break;
    case Provision::maped: munmap(data, size); break;
    }
    data = nullptr;
}

#elif _WIN32

#else

#endif



File::File(const char* filename, File::State state) :
    state(state), fileHandle((intptr_t)-1), buffer(nullptr), buffer_size(0) {
    init(filename, state);

}


inline void File::alloc_buffer(size_t size) {
    if (buffer_size == size) return;
    free(buffer);
    buffer = reinterpret_cast<char*>(malloc(size + 1));
    if (buffer == nullptr) std::bad_alloc();
    buffer[size] = '\0';
    buffer_size = size;
}



#ifdef _WIN32
// Windows implemintation
# include <windows.h>

void File::open(const char* name, State state) {
    DWORD creation;
    DWORD flags = FILE_FLAG_SEQUENTIAL_SCAN;
    DWORD access = GENERIC_READ;
    DWORD share = FILE_SHARE_READ;

    switch (state) {
    case State::read:
        creation = OPEN_EXISTING;
        share |= FILE_SHARE_WRITE;
        break;
    case State::write:
        creation = CREATE_ALWAYS;
        access |= GENERIC_WRITE;
        break;
    case State::append:
        creation = OPEN_ALWAYS;
        access |= GENERIC_WRITE;
    }
    fileHandle = (intptr_t)CreateFileA(name, access, share, nullptr, creation, flags, nullptr);
    if (notOpen()) throw std::runtime_error("Failed to open file");
}

void File::close() {
    if (!notOpen()) CloseHandle((void*)fileHandle);
    free(buffer);
    buffer = nullptr;
}

inline bool File::notOpen() {
    return fileHandle == (intptr_t)INVALID_HANDLE_VALUE;
}


size_t File::write(const char* buffer, size_t length) {
    if (notOpen()) throw std::runtime_error("File not open");
    DWORD writen;
    WriteFile((void*)fileHandle, buffer, length, &writen, nullptr);
    return writen;
}

size_t File::read(size_t size) {
    if (notOpen()) throw std::runtime_error("File not open");
    if (!size) {
        LARGE_INTEGER winapi_bullshit_long;
        GetFileSizeEx((void*)fileHandle, &winapi_bullshit_long);
        size = winapi_bullshit_long.QuadPart;
    }
    alloc_buffer(size);
    DWORD bytes_read;
    ReadFile((void*)fileHandle, buffer, size, &bytes_read, nullptr);
    return static_cast<size_t>(bytes_read);
}

#elif __linux__


size_t File::write(const char* data, size_t length) {
    if (notOpen()) throw std::runtime_error("File not open");
    size_t readen = ::write((int)fileHandle, data, length);
    if (readen == (size_t)-1) std::runtime_error("Failed to write");
    return readen;
}

size_t File::read(size_t size) {
    if (notOpen()) throw std::runtime_error("File not open");
    if (!size) {

    }
    alloc_buffer(size);
    return (size_t)::read(fileHandle, buffer, size);
}
#endif

