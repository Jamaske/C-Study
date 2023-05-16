#pragma once
#include <cstring>

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

    DynArr<T>& operator=(DynArr const&  Rvalue);
    DynArr<T>& operator=(DynArr&& Lvalue) noexcept ;

    size_t get_size();
    T& operator[](size_t idx);//get/put content from/at existing index
    T& get(size_t idx, T& _default = 0);//get content from existing index or create new with default value and return it
    void insert(size_t idx,const T& value);//put content to existing index or create new one
    void append(const T& value);//create new index at the end of the array and put value there
    const T& peek();//return element from the end of the array
    T pop();//delete and return element from the end of the array

};

#include "DynArr.tpp"










