#include <iostream>



int main(){
    int a = 68743654;
    int mask = 0x11111111;
    short i = 28;
    int exp;
    do{
         exp = a;
         exp |= a>>1;
         exp &= a>>2;
         exp |= a>>3;
         exp &= mask<<(i--);
         exp |= exp << 1; //exp *= 3
         a += exp;
    } while (i);

    for(i = 0; i < 8; ++i){
        std::cout << (char)((a & 0x0000000F) + 48);
        a >>= 4;
    }


}