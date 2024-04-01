#include <typeinfo>
#include <cstdio>

int main() {

    //pointer aarithmetic 
    int* ptr = nullptr;
    int shift = 2;

    (ptr + shift) == (int*)((char*)ptr + shift * sizeof(int)); 
    // true expression
    //same int* adreses (2 ints)/(8 bytes) after 0 (null) adress


    //array access operator
    constexpr int  arr[] = { 1,2,3,4,5 };
    constexpr int idx = 3;

    static_assert(arr[idx] == 4);
    static_assert(idx[arr] == 4);
    static_assert(*(arr + idx) == 4);
    static_assert(*(idx + arr) == 4);
    //none of them failed
    //arr[idx] = *(arr + idx) = *(idx + arr) = idx[arr]

    return 0;
}
