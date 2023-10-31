


#include <cstdint>
#include <iostream>


struct heap_array{
    uint64_t** storage;
    heap_array(std::size_t height, std::size_t width)
        {
        storage = new uint64_t * [height];
        for(uint64_t** it = storage; it < storage + height; ++it){
            *it = new uint64_t[width] {0};
        }
    }
    uint64_t* operator[](std::size_t idx){
        return storage[idx];
    }
};

template<int height>
struct half_array{
    uint64_t* storage[height];
    half_array(std::size_t width):
    storage{0}
    {
        for(uint64_t** it = storage; it < storage + height; ++it){
            *it = new uint64_t[width] {0};
        }
    }
    uint64_t* operator[](std::size_t idx){
        return storage[idx];
    }
};


template<int height, int width >
struct stack_array{
    uint64_t storage[height][width];
    stack_array():
    storage{0}
    {}
    uint64_t* operator[](std::size_t idx){
        return storage[idx];
    }
};

template<int height, int width>
struct emulated_2d{
    uint64_t storage[height * width];
    emulated_2d():
    storage(0){}
    uint64_t* operator[](std::size_t idx){
        return &storage[idx * width];
    }
};


template<typename T,int len>
struct nested1d{
    T storage[len];
    nested1d():
            storage{}{
    }
    T& operator[](std::size_t idx){
        return storage[idx];
    }

};


int main(){
    stack_array<100,100> stackArray;
    stackArray[76][95] = 1;
    std::cout << stackArray[76][95] << '\n';

    half_array<100> halfArray(100);
    halfArray[76][95] = 2;
    std::cout << halfArray[76][95] << '\n';

    heap_array heapArray(100,100);
    heapArray[25][65] = 3;
    std::cout << heapArray[25][65] << '\n';

    emulated_2d<100,100> emulated2D;
    emulated2D[67][42] = 4;
    std::cout << emulated2D[67][42] << '\n';

    nested1d<nested1d<uint64_t, 100>, 100> nested2D {};
    nested2D[23][62] = 5;
    std::cout << nested2D[23][62] << '\n';

}