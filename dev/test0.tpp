#pragma once
template<typename T>
struct mystruct{
    T data;
    mystruct(T input);
    T do_somethiong(T input);
};


template<typename T>
mystruct<T>::mystruct(T input){
    mystruct<T>::data = input;
}

template<typename T>
T mystruct<T>::do_somethiong(T input){
    return input;
}


