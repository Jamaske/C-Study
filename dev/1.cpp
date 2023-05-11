#include <iostream>
//#include "PriorQueue.h"

bool comparator(int a, int b){
    return a < b;
}

void wrapper(int first, int second, bool(*cmp)(int, int)){
    std::cout << cmp(first, second);
}

template<typename T, typename cmp>
void wrapper2(T first, T second){
    std::cout << cmp(first, second);
}

int main(){
    wrapper(5,6, comparator);
    wrapper2<int, comparator>(5, 6);




}