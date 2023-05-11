#pragma once
#include "DynArr.h"

template<typename T>
class PriorQueue{
    DynArr<T> data;
    size_t size;

public:
    PriorQueue();//constructor
    ~PriorQueue();
    PriorQueue(PriorQueue& Rvalue_src);//copy constructor
    PriorQueue(PriorQueue&& Lvalue_src) noexcept ;//move constructor
    PriorQueue<T>& operator=(PriorQueue const& Rvalue);//copy assigment
    PriorQueue<T>& operator=(PriorQueue && Lvalue) noexcept;//move assigment

    void add(T new_obj);
    const T& peek_top();
    T pop_top();
private:
    void bubble_up(size_t idx);
    void bubble_down(size_t idx);
};

//basic class stuff
template<typename T>
PriorQueue<T>::PriorQueue(): data(DynArr<T>()), size(0){}

template<typename T>
PriorQueue<T>::~PriorQueue() {
    data.~DynArr();
}

template<typename T>
PriorQueue<T>::PriorQueue(PriorQueue &Rvalue_src): data(Rvalue_src.data), size(Rvalue_src.size) {}

template<typename T>
PriorQueue<T>::PriorQueue(PriorQueue &&Lvalue_src) noexcept:
    data(Lvalue_src.data), size(Lvalue_src.size) {//might not really move but copy
}



template<typename T>
PriorQueue<T> &PriorQueue<T>::operator=(const PriorQueue &Rvalue) {
    data = Rvalue.data;
    size = Rvalue.size;
    return *this;
}

template<typename T>
PriorQueue<T> &PriorQueue<T>::operator=( PriorQueue &&Lvalue)  noexcept {
    data = Lvalue.data;//same thing
    std::swap(size, Lvalue.size);
    return *this;
}


template<typename T>
void PriorQueue<T>::add(T new_obj) {
    data.append(new_obj);
    size = data.get_size();
    bubble_up(size - 1);
}

template<typename T>
const T &PriorQueue<T>::peek_top() {

}

template<typename T>
T PriorQueue<T>::pop_top() {
    return nullptr;
}

template<typename T>
void PriorQueue<T>::bubble_up(size_t idx) {

}

template<typename T>
void PriorQueue<T>::bubble_down(size_t idx) {

}
