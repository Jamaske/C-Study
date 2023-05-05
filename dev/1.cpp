#include <iostream>
#include "DynArr.h"

int main(){
    uint64_t a = (uint64_t)1 << 32;
    uint64_t a0001 = a >> 10;
    uint64_t b = 0;
    std::cout << "Start" << a << "\n";
    for(size_t i = 0; i < 1 << 10; ++i) {
        std::cout << (0.1*i) << "%\n";
        for (size_t j = 0; j < a0001; ++j) {
            b ^= i;
        }
    }
    std::cout << "Done" << b << "\n";
}