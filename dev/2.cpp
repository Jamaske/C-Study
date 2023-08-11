#include <iostream>
#include <bitset>


#include <chrono>
using namespace std::chrono;

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

void hend_maid(){
    for (uint64_t a = 9999999999999999; a > 9999999999999999 - 1000000; --a) {
        //std::cout << a << std::endl;
        //std::cout << std::bitset<64>(a) << std::endl;
        uint64_t b = bin_to_bcd(a);
        //std::cout << std::bitset<64>(b) << std::endl;
        char *charr = bcd_to_charr(b);
        std::string str = std::string(charr);
        //std::cout << std::string(charr) << std::endl;
    }
}

const char DigitTens[] = {
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
        '2', '2', '2', '2', '2', '2', '2', '2', '2', '2',
        '3', '3', '3', '3', '3', '3', '3', '3', '3', '3',
        '4', '4', '4', '4', '4', '4', '4', '4', '4', '4',
        '5', '5', '5', '5', '5', '5', '5', '5', '5', '5',
        '6', '6', '6', '6', '6', '6', '6', '6', '6', '6',
        '7', '7', '7', '7', '7', '7', '7', '7', '7', '7',
        '8', '8', '8', '8', '8', '8', '8', '8', '8', '8',
        '9', '9', '9', '9', '9', '9', '9', '9', '9', '9',
} ;

const char DigitOnes[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
} ;

 std::string* getChars(uint64_t i) {
     char buf[16];
     uint64_t q, r;
     int charPos = 16;

     // Generate two digits per iteration
     while (i >= 100) {
         q = i / 100;
         r = i - (q * 100);
         i = q;
         buf[--charPos] = DigitOnes[r];
         buf[--charPos] = DigitTens[r];
     }

     // We know there are at most two digits left at this point.
     buf[--charPos] = DigitOnes[i];
     if (i > 9) {
         buf[--charPos] = DigitTens[i];
     }


     return new std::string(buf);
 }
void premaid(){
    for (uint64_t a = 9999999999999999; a > 9999999999999999 - 1000000; --a) {
        std::string str = *getChars(a);
    }
}


int main(){//9999999999999999

    for(uint64_t i = 0; i < 100; i++) {
        auto start = high_resolution_clock::now();
        premaid();
        auto stop = high_resolution_clock::now();
        auto duration = (duration_cast<milliseconds>(stop - start));//nanoseconds on 1 call
        std::cout << "million=" << i << "\tduration: " << duration.count() << std::endl;

    }






}