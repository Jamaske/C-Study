#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <array>
#include <bitset>
#include <iostream>

typedef unsigned short u16;
typedef std::array<u16, 8> mesh;
typedef unsigned long long u64;


mesh data



{
    0b0000000000000000,
    0b1111001000111100,
    0b1111101100111100,
    0b1111110001111110,
    0b1111111001111110,
    0b1111001111001111,
    0b0111101101100110,
    0b0000000000000000,
};

mesh lo_edge{};
mesh lo_border{};
mesh hi_edge{};
mesh hi_border{};





void print(mesh data) {
    for (auto row : data) {
        std::cout << std::bitset<8>(row >> 8) << ' ' << std::bitset<8>(row & 0x00FFu) << '\n';
    }
    std::cout << std::endl;
}

void print_all() {
    std::cout << "data\n";
    print(data);
    std::cout << "hi border\n";
    print(hi_border);
    std::cout << "hi edge\n";
    print(hi_edge);
    std::cout << "lo edge\n";
    print(lo_edge);
    std::cout << "lo border\n";
    print(lo_border);

}

int main()
{



    u16 le = 0;
    u16 hb = 0;
    for (u64 i = 0; i < data.size(); ++i) {
        u16 row = data[i];
        u16 row_r = row >> 1;
        u16 row_l = row << 1;
        hi_edge[i] = row & ~row_r;
        lo_border[i] = ~row & row_r;
        lo_edge[i] = row & ~row_l;
        hi_border[i] = ~row & row_l;
    }



    print_all();


    return 0;
}