//
// Created by Master on 20.10.2023.
//



#include <cstdint>

uint64_t bin_to_bcd(uint64_t bin, const uint8_t first_1_idx = 53){
    if(bin > 9999999999999999) return -1;
    if(first_1_idx > 53) return -2;

    uint8_t bit = first_1_idx - 1;
    uint64_t expression;
    while (bit  >= 5){
        expression = (((bin>>0) | (bin>>1)) & (bin>>2) | (bin>>3)) & 0x1111111111111111 << --bit;
        bin += expression | expression << 1;
        expression = (((bin>>0) | (bin>>1)) & (bin>>2) | (bin>>3)) & 0x1111111111111111 << --bit;
        bin += expression | expression << 1;
        expression = (((bin>>0) | (bin>>1)) & (bin>>2) | (bin>>3)) & 0x1111111111111111 << --bit;
        bin += expression | expression << 1;
        expression = (((bin>>0) | (bin>>1)) & (bin>>2) | (bin>>3)) & 0x1111111111111111 << --bit;
        bin += expression | expression << 1;
    }
    switch (bit) {
        case 4:
            expression = (((bin>>0) | (bin>>1)) & (bin>>2) | (bin>>3)) & 0x1111111111111111 << 3;
            bin += expression | expression << 1;
        case 3:
            expression = (((bin>>0) | (bin>>1)) & (bin>>2) | (bin>>3)) & 0x1111111111111111 << 2;
            bin += expression | expression << 1;
        case 2:
            expression = (((bin>>0) | (bin>>1)) & (bin>>2) | (bin>>3)) & 0x1111111111111111 << 1;
            bin += expression | expression << 1;
    }
    return bin;
}
char* bcd_to_charr(uint64_t bcd, uint8_t charr_len = 16){
    char* charr = new char[charr_len];
    uint8_t bit;

    for(bit = 0; charr_len >= 4; bit += 16){
        charr_len -= 4;
        charr[charr_len + 3] = (char)((bcd >> bit      & 0x000000000000000F) + 48);
        charr[charr_len + 2] = (char)((bcd >> bit + 4  & 0x000000000000000F) + 48);
        charr[charr_len + 1] = (char)((bcd >> bit + 8  & 0x000000000000000F) + 48);
        charr[charr_len    ] = (char)((bcd >> bit + 12 & 0x000000000000000F) + 48);
    }
    switch (charr_len) {
        case 3:
            charr[2] = (char)((bcd >> bit     & 0x000000000000000F) + 48);
        case 2:
            charr[1] = (char)((bcd >> bit + 4 & 0x000000000000000F) + 48);
        case 1:
            charr[0] = (char)((bcd >> bit + 8 & 0x000000000000000F) + 48);
    }
    return charr;
}

void bitwisemagic(){
    for (uint64_t a = bunch_start; a < bunch_end; ++a) {
        //std::cout << a << std::endl;
        //std::cout << std::bitset<64>(a) << std::endl;
        uint64_t b = bin_to_bcd(a);
        //std::cout << std::bitset<64>(b) << std::endl;
        char *charr = bcd_to_charr(b);
        std::string str = std::string(charr);
        //std::cout << std::string(charr) << std::endl;
    }
}