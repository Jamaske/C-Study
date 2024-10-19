#include <windows.h>
#include <stdexcept>
#include "File.h"

File::File(const char* filename, File::Mode mode) :
    fileHandle(nullptr), read_buffer(nullptr), buffer_size(0), isOpen(false) {
    open(filename, mode);
}

File::~File() {
    close();
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
    case Mode::append:
        creation = OPEN_ALWAYS;
        access |= GENERIC_WRITE;
    }
    fileHandle = CreateFileA(name, access, share, nullptr, creation, flags, nullptr);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Failed to open file");
    }
    isOpen = true;
}

void File::close() {
    if (isOpen) {
        CloseHandle(fileHandle);
        isOpen = false;
    }
    if (buffer_size) {
        free(read_buffer);
        buffer_size = 0;
    }
}

void File::get_buffer(size_t size) {
    if (buffer_size >= size) return;
    read_buffer = reinterpret_cast<char*>(malloc(size));
    if (read_buffer == nullptr) std::bad_alloc();
    buffer_size = size;
}


#include <iostream>
size_t File::write(const char* buffer, size_t length) {
    if (!isOpen) throw std::runtime_error("File not open");
    DWORD writen;
    WriteFile(fileHandle, buffer, length, &writen, nullptr);
    return writen;
}

size_t File::read(const char*& data, size_t size) {
    if (!isOpen) throw std::runtime_error("File not open");
    get_buffer(size + 1);
    DWORD bytes_read;
    ReadFile(fileHandle, read_buffer, size, &bytes_read, nullptr);
    read_buffer[bytes_read] = '\0';
    data = read_buffer;
    return static_cast<size_t>(bytes_read);
}
#elif __linux__
#include "File.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
void File::opne(const char* name, Mode mode) {
    int flag = 0;
}


#endif

