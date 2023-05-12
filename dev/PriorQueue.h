#pragma once
#include "DynArr.h"

template<typename T, bool (*cmp)(T, T)>
class PriorQueue{
    DynArr<T> data;
    size_t size;

public:
    PriorQueue();//constructor
    ~PriorQueue();
    PriorQueue(PriorQueue<T, bool (*cmp)>& Rvalue_src);//copy constructor
    PriorQueue(PriorQueue<T, bool (*cmp)>&& Lvalue_src) noexcept ;//move constructor
    PriorQueue<T, bool (*cmp)>& operator=(PriorQueue<T, bool (*cmp)> const& Rvalue);//copy assigment
    PriorQueue<T, bool (*cmp)>& operator=(PriorQueue<T, bool (*cmp)> && Lvalue) noexcept;//move assigment

    bool not_empty();
    void add(T new_obj);
    const T& peek_top();
    T pop_top();
    T get_item(size_t idx);
    void change_item(size_t idx, T value);
private:
    void bubble_up(size_t idx);
    void bubble_down(size_t idx);
};

//basic class stuff
template<typename T, bool (*cmp)(T, T)>
PriorQueue<T, &cmp>::PriorQueue():
    data(DynArr<T>()), size(0){}

template<typename T, bool (*cmp)(T, T)>
PriorQueue<T, &cmp>::~PriorQueue() {
    data.~DynArr();
}

template<typename T, bool (*cmp)(T, T)>
PriorQueue<T, &cmp>::PriorQueue(PriorQueue<T, &cmp> &Rvalue_src):
    data(Rvalue_src.data), size(Rvalue_src.size) {}

template<typename T, bool (*cmp)(T, T)>
PriorQueue<T, &cmp>::PriorQueue(PriorQueue<T, &cmp> &&Lvalue_src) noexcept:
    data(Lvalue_src.data), size(Lvalue_src.size) {//might not really move but copy
}



template<typename T, bool (*cmp)(T, T)>
PriorQueue<T, &cmp> &PriorQueue<T, &cmp>::operator=(const PriorQueue<T, &cmp> &Rvalue) {
    data = Rvalue.data;
    size = Rvalue.size;
    return *this;
}

template<typename T, bool (*cmp)(T, T)>
PriorQueue<T, &cmp> &PriorQueue<T, &cmp>::operator=( PriorQueue<T, &cmp> &&Lvalue)  noexcept {
    data = Lvalue.data;//same thing
    std::swap(size, Lvalue.size);
    return *this;
}


template<typename T, bool (*cmp)(T, T)>
void PriorQueue<T, &cmp>::add(T new_obj) {
    data.append(new_obj);
    size = data.get_size();
    bubble_up(size - 1);
}

template<typename T, bool (*cmp)(T, T)>
const T &PriorQueue<T, &cmp>::peek_top() {
    return data[0];
}

template<typename T, bool (*cmp)(T, T)>
T PriorQueue<T, &cmp>::pop_top() {
    T ret = data[0];
    data[0] = data.pop();
    size = data.get_size();
    bubble_down(0);
}

template<typename T, bool (*cmp)(T, T)>
bool PriorQueue<T, &cmp>::not_empty() {
    return size;
}

template<typename T, bool (*cmp)(T, T)>
T PriorQueue<T, cmp>::get_item(size_t idx) {
    return data[idx];
}

template<typename T, bool (*cmp)(T, T)>
void PriorQueue<T, cmp>::change_item(size_t idx, T value) {
    T prev_value = data[idx];
    data[idx] = value;
    if(cmp(value, prev_value)){
        bubble_up(idx);
    }
    else{
        bubble_down(idx);
    }
}

template<typename T, bool (*cmp)(T, T)>
void PriorQueue<T, &cmp>::bubble_up(size_t idx) {
    while(idx){//пока не в корне
        size_t parent_idx = (idx - 1) >> 1;
        if (cmp(data[parent_idx], data[idx])) return;//проверка на упорядоченность
        std::swap(data[parent_idx], data[idx]);
        idx = parent_idx;
    }
}

template<typename T, bool (*cmp)(T, T)>
void PriorQueue<T, &cmp>::bubble_down(size_t idx) {
    size_t dot2 = (idx << 1) + 2;
    size_t better_child;
    while(dot2 < size){//пока обе дочерних вершины существуют
        better_child = dot2 - cmp(data[dot2 - 1], data[dot2]);
        if (cmp(data[idx], data[better_child])) break;
        std::swap(cmp(data[idx], data[better_child]);
        idx = better_child;
        dot2 = (idx << 1) + 2;
    }

    size_t dot1 = (idx << 1) + 1;
    if(dot1 < size && cmp(data[dot1], data[idx])){//проверка на случай существования только 1 ребёнка
        std::swap(cmp(data[dot1], data[idx])
    }
}