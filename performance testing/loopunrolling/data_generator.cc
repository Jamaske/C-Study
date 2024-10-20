#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include "../file works/File.h"

int main() {
    File file("data.bin", File::Mode::write);

    const int N = 1024; //* 1024 * 256;
    static uint16_t ints_arr[N];
    for (int i = 0; i < N; ++i) {
        ints_arr[i] = (short)rand();
    }
    size_t writen = file.write(reinterpret_cast<char*>(&ints_arr), N * sizeof(uint16_t));
    //while (true);
    std::cout << "Done!!! \t" << writen << " bytes is writen" << std::endl;

    file.close();

    File src("data.bin", File::Mode::read);
    size_t read = src.read();
    std::cout << src.buffer << "\nReadend bytes from file: " << read << std::endl;
}