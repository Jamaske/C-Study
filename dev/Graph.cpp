#include <iostream>

template<size_t len>
struct bitset{
    uint64_t arr[((len-1)>>6) + 1];
    bool operator[](size_t idx){
        std::cout << '\n' << (idx >> 6) << '\n';
        return arr[idx >> 6] & (1 << (idx & 63));
    }

};




int main(){
    bitset<65> set;
    std::cout << sizeof(set);
    set.arr[1] = 1;
    std::cout << set[63];
}