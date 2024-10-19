#ifndef FILE_H
#define FILE_H

#include <string>
#include <stdexcept>

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

    File(const char* filename, Mode mode);
    ~File();

    size_t write(const char* data, size_t length);
    size_t read(const char*& data, size_t size);
    void close();
    inline size_t get_buffer_size() const { return buffer_size; }

private:
    void get_buffer(size_t size);
    void open(const char* filename, Mode mode);
    void* fileHandle; // Internal file handle (platform-specific)
    char* read_buffer;
    size_t buffer_size;
    bool isOpen;
};

#endif // FILE_H
