#include <iostream>
#include <functional>
//#include "PriorQueue.h"

//template<typename Type>
//struct Compare
//{
//    Compare() {}
//
//    bool operator()(Type a, Type b) {}
//};

bool comparator(int a, int b){
    return a < b;
}



void wrapper(int first, int second, bool(*cmp)(int, int)){
    std::cout << cmp(first, second);
}

template<typename T, cmp>
void wrapper2(T first, T second){
    std::cout << cmp(first, second);
}


template<typename T, T inc>
T incriment(T& a){
    a += inc;
    return a;
}

int main(){
    wrapper(5,6, comparator);
    int number = 6;
    incriment<int, 5>(number);
    std::cout << number << '\n';
    wrapper2<int, std::function<bool(int, int)>>(5, 6);




}

