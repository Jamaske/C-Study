#pragma once
#include "DynArr.h"

template<typename T>
class PriorQueue{
    DynArr<T> data;
    size_t size;

public:
    PriorQueue();//constructor
    ~PriorQueue();
    PriorQueue(PriorQueue<T>& Rvalue_src);//copy constructor
    PriorQueue(PriorQueue<T>&& Lvalue_src) noexcept ;//move constructor
    PriorQueue<T>& operator=(PriorQueue<T> const& Rvalue);//copy assigment
    PriorQueue<T>& operator=(PriorQueue<T> && Lvalue) noexcept;//move assigment

    bool not_empty();
    const T& peek_top();
    T pop_top();
    T get_item(size_t idx);
    void add(T new_obj);
    void change_item(size_t idx, T value);
private:
    void sieve_up(size_t idx);
    void sieve_down(size_t idx);
};

//basic class stuff
template<typename T>
PriorQueue<T>::PriorQueue():
    data(DynArr<T>()), size(0){}

template<typename T>
PriorQueue<T>::~PriorQueue() {
    data.~DynArr();
}

template<typename T>
PriorQueue<T>::PriorQueue(PriorQueue<T> &Rvalue_src):
    data(Rvalue_src.data), size(Rvalue_src.size) {}

template<typename T>
PriorQueue<T>::PriorQueue(PriorQueue<T> &&Lvalue_src) noexcept:
    data(Lvalue_src.data), size(Lvalue_src.size) {//might not really move but copy
}

template<typename T>
PriorQueue<T> &PriorQueue<T>::operator=(const PriorQueue<T> &Rvalue) {
    data = Rvalue.data;
    size = Rvalue.size;
    return *this;
}

template<typename T>
PriorQueue<T> &PriorQueue<T>::operator=( PriorQueue<T> &&Lvalue)  noexcept {
    data = Lvalue.data;//same thing
    std::swap(size, Lvalue.size);
    return *this;
}



template<typename T>
void PriorQueue<T>::add(T new_obj) {
    data.append(new_obj);
    size = data.get_size();
    sieve_up(size - 1);
}

template<typename T>
const T &PriorQueue<T>::peek_top() {
    return data[0];
}

template<typename T>
T PriorQueue<T>::pop_top() {
    T ret = data[0];
    data[0] = data.pop();
    size = data.get_size();
    sieve_down(0);
}

template<typename T>
bool PriorQueue<T>::not_empty() {
    return size;
}

template<typename T>
T PriorQueue<T>::get_item(size_t idx) {
    return data[idx];
}

template<typename T>
void PriorQueue<T>::change_item(size_t idx, T value) {
    T prev_value = data[idx];
    data[idx] = value;
    if(cmp(value, prev_value)){
        sieve_up(idx);
    }
    else{
        sieve_down(idx);
    }
}

template<typename T>
void PriorQueue<T>::sieve_up(size_t idx) {
    while(idx){//пока не в корне
        size_t parent_idx = (idx - 1) >> 1;
        if (data[parent_idx] > data[idx]) return;//проверка на упорядоченность
        std::swap(data[parent_idx], data[idx]);
        idx = parent_idx;
    }
}

template<typename T>
void PriorQueue<T>::sieve_down(size_t idx) {
    size_t dot2 = (idx << 1) + 2;
    size_t better_child;
    while(dot2 < size){//пока обе дочерних вершины существуют
        better_child = dot2 - (data[dot2 - 1] > data[dot2]);
        if (data[idx] > data[better_child]) break;
        std::swap(data[idx], data[better_child]);
        idx = better_child;
        dot2 = (idx << 1) + 2;
    }

    size_t dot1 = dot2 - 1;
    if(dot1 < size && data[dot1] > data[idx]){//проверка на случай существования только 1 ребёнка
        std::swap(data[dot1], data[idx]);
    }
}