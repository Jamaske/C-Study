#include <iostream>
#include <functional>

typedef uint64_t ul;
typedef uint32_t ui;


struct uint1024 {
    ul arr[16];

    uint1024(std::string n){

        arr[0] = 0;
    }


    uint1024():
    arr{0}
    {}

};

int main(){
    std::cout << ((short)5 >> 1);



}