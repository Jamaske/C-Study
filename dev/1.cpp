#include <iostream>
#include "DynArr.h"

int main(){
    DynArr<int> a;
    for(int i = 0; i <= 20; ++i){
        a.append(i*i);
    }

    a.insert(1677, 15);
    std::cout << a.pop();
    for(int i = 0; i < a.get_size(); ++i){
        std::cout << a[i] << '\n';
    }



}