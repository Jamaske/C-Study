#include <stdexcept>
#include "File.h"

File::File(const char* filename, File::Mode mode) :
    mode(mode), fileHandle((intptr_t)-1), buffer(nullptr), buffer_size(0) {
    open(filename, mode);

}

File::~File() {
    close();
}

inline void File::get_buffer(size_t size) {
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

void File::open(const char* name, Mode mode) {
    DWORD creation;
    DWORD flags = FILE_FLAG_SEQUENTIAL_SCAN;
    DWORD access = GENERIC_READ;
    DWORD share = FILE_SHARE_READ;

    switch (mode) {
    case Mode::read:
        creation = OPEN_EXISTING;
        share |= FILE_SHARE_WRITE;
        break;
    case Mode::write:
        creation = CREATE_ALWAYS;
        access |= GENERIC_WRITE;
        break;
    case Mode::append:
        creation = OPEN_ALWAYS;
        access |= GENERIC_WRITE;
    }
    fileHandle = (intptr_t)CreateFileA(name, access, share, nullptr, creation, flags, nullptr);
    if (fileHandle == (intptr_t)INVALID_HANDLE_VALUE) throw std::runtime_error("Failed to open file");
    isOpen = true;
}

void File::close() {
    if (isOpen) {
        CloseHandle((void*)fileHandle);
        isOpen = false;
    }
    if (buffer_size) {
        free(buffer);
        buffer_size = 0;
    }
}


size_t File::write(const char* buffer, size_t length) {
    if (!isOpen) throw std::runtime_error("File not open");
    DWORD writen;
    WriteFile((void*)fileHandle, buffer, length, &writen, nullptr);
    return writen;
}

size_t File::read(const char*& data, size_t size) {
    if (!isOpen) throw std::runtime_error("File not open");
    get_buffer(size + 1);
    DWORD bytes_read;
    ReadFile((void*)fileHandle, buffer, size, &bytes_read, nullptr);
    buffer[bytes_read] = '\0';
    data = buffer;
    return static_cast<size_t>(bytes_read);
}

#elif __linux__

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
void File::open(const char* name, Mode mode) {
    int flag = 0;
    switch (mode) {
    case Mode::read:
        flag = O_RDONLY;
        break;
    case Mode::write:
        flag = O_WRONLY | O_CREAT | O_TRUNC;
        break;
    case Mode::append:
        flag = O_WRONLY | O_CREAT | O_APPEND;
        break;
    }
    fileHandle = (intptr_t)::open(name, flag, S_IRUSR | S_IWUSR);
    if (fileHandle == -1) throw std::runtime_error("Failed to open file");
}

void File::close() {
    if (fileHandle != -1LL) ::close((int)fileHandle);
    fileHandle = -1LL;
    free(buffer);
    buffer = nullptr;
}


/*
size_t File::get_file_size(){
    stat sb;
    if(fstat((int)fileHandle, &sb) == -1)

}
*/

size_t File::write(const char* data, size_t length) {
    if (fileHandle == -1LL) throw std::runtime_error("File not open");
    size_t readen = ::write((int)fileHandle, data, length);
    if (readen == (size_t)-1) std::runtime_error("Failed to write");
    return readen;
}

size_t File::read(size_t size) {
    if (fileHandle == -1LL) throw std::runtime_error("File not open");
    if (!size) {
        struct stat prop;
        if (fstat((int)fileHandle, &prop) == -1) throw std::runtime_error("Cant access file propertys");
        size = prop.st_size;
    }
    get_buffer(size);
    return (size_t)::read(fileHandle, buffer, size);
}
#endif

