#include <iostream>
#include "better_for.h"


static int a = 0, b = 1, n = 0;
void next_fib(){
    int c = a + b;
    a = b;
    b = c;
    n++;
    //std::cout << "in next_fib" << std::endl;
}


int main(){
    std::cout << "star" << std::endl;
    better_for(1000000000000, &next_fib);
    std::cout << b << std::endl << n << std::endl;
}

