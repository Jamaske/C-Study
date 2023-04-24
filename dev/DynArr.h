#pragma once
#include <cstring>
#include <vector>

template<typename T>
class DynArr{
    T*storage;
    size_t allocation;
    size_t size;

    static const size_t base_allocation = 16;

    explicit DynArr(size_t allocation);
    void resize(size_t new_allocation);
public:
    explicit DynArr();
    DynArr(DynArr& src);
    DynArr(DynArr&& src) noexcept ;
    ~DynArr();
    std::vector<T> a;


    DynArr<T>& operator=(DynArr const&  Rvalue);
    DynArr<T>& operator=(DynArr&& Lvalue) noexcept ;

    T& operator[](size_t idx);//get/put content from/at existing index
    T& get(size_t idx, T& _default = 0);//get content from existing index or create new with default value and return it
    void insert(size_t idx,const T& value);//put content to existing index or create new one
    void append(const T& value);//create new index at the end of the array and put value there
    const T& peek();//return element from the end of the array
    T pop();//delete and return element from the end of the array

};


template<typename T>//basic constructor
DynArr<T>::DynArr(size_t allocation):
    allocation(allocation), size(0){
    storage = new T[allocation] {0};
}

template<typename T>//user constructor
DynArr<T>::DynArr(): DynArr(base_allocation) {}

template<typename T>//careful copy constructor
DynArr<T>::DynArr(DynArr &src): DynArr(src.allocation){
    std::memcpy(storage, src.storage, allocation * sizeof(T));
    size = src.size;
}

template<typename T>//destructive copy constructor
DynArr<T>::DynArr(DynArr &&src) noexcept:
    size(0), allocation(0), storage(nullptr){
    std::swap(src.size, size);
    std::swap(src.allocation, allocation);
    std::swap(src.storage, storage);
}


template<typename T>
DynArr<T>::~DynArr() {
    delete[] storage;
}

template<typename T>
DynArr<T>& DynArr<T>::operator=(DynArr const& Rvalue) {
    if(this != &Rvalue) {
        if (allocation != Rvalue.allocation) {
            delete[] storage;
            allocation = Rvalue.allocation;
            storage = new T[allocation];
        }
        std::memcpy(storage, Rvalue.storage, allocation * sizeof(T));
    }
    return *this;
}

template<typename T>
DynArr<T>& DynArr<T>::operator=(DynArr&& Lvalue) noexcept {
    std::swap(Lvalue.storage, storage);
    std::swap(Lvalue.allocation, allocation);
    std::swap(Lvalue.size, size);
    return *this;
}

template<typename T>
T &DynArr<T>::operator[](const size_t idx) {

    if(idx >= allocation){
        size_t new_allocation;
        do {
            new_allocation = allocation < 1;
        } while (idx >= new_allocation);
        resize(new_allocation);
    }
    return storage[idx];
}

template<typename T>
void DynArr<T>::resize(size_t new_allocation) {
    if(allocation == new_allocation) return;
    T* new_storage = new T[new_allocation];
    std::memcpy(storage, new_storage, std::min(allocation, new_allocation) * sizeof(T));
    delete[] storage;
    storage = new_storage;
    allocation = new_allocation;
    size = std::min(size, allocation);
}

template<typename T>
T &DynArr<T>::get(size_t idx, T &_default) {
    if(idx >= size) {
        return _default;
    }
    return storage[idx];
}

template<typename T>
void DynArr<T>::insert(size_t idx, const T &value) {
    if (idx >= allocation){
        size_t new_allocation = allocation;
        while (idx >= (new_allocation <<= 1));
        resize(new_allocation);
    }
    storage[idx] = value;
}

template<typename T>
void DynArr<T>::append(const T &value) {
    if(size >= allocation) resize(allocation << 1);
    storage[size++] = value;
}

template<typename T>
const T &DynArr<T>::peek() {
    return storage[size - 1];
}

template<typename T>
T DynArr<T>::pop() {
    if( (--size << 2) <= allocation) resize(allocation >> 1);
    return storage[size];
}













