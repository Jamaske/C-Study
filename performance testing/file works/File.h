#ifndef FILE_H
#define FILE_H

#include <string>
#include <stdexcept>
#include <stdint.h>

class File {
private:
    struct Handle {
        intptr_t file;
        size_t size;
        enum State {
            close,
            read,//radonly
            write,//overwrite
            both,//read&write
            append,//loging
        } state;
        Handle();
        ~Handle();
        void init(State state, const char* filename = nullptr);
        void close();
        bool isOpen();
    } handle;
public:
    struct Buffer {
        char* data;
        size_t size;
        enum Provision {
            stack,
            malloc,
            maped
        } provision;
        Buffer();
        ~Buffer();
        void set(Provision provision, size_t size, intptr_t arg = -1);
        void free();
    } buffer;


    File(const char* filename, State state);
    ~File();

    size_t write(const char* data, size_t length);
    size_t read(size_t size = 0);

    ///size_t get_file_size();
};

#endif // FILE_H
