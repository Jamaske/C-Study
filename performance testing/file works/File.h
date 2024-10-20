#ifndef FILE_H
#define FILE_H

#include <string>
#include <stdexcept>
#include <stdint.h>

class File {
public:
    enum class Mode {
        read,
        write,
        append,
        /*
        text_write_read,
        byte_write_read,
        text_append,
        byte_append,
        */
    };
private:
    Mode mode;
    intptr_t fileHandle; // Internal file handle (platform-specific)
public:
    char* buffer;
    size_t buffer_size;

    File(const char* filename, Mode mode);
    ~File();

    size_t write(const char* data, size_t length);
    size_t read(size_t size = 0);
    void close();
    bool notOpen();

    ///size_t get_file_size();

private:
    void get_buffer(size_t size);
    void open(const char* filename, Mode mode);
};

#endif // FILE_H
