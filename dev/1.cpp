#include <iostream>
#include <cmath>

typedef uint64_t ul;

ul rand64(){
    ul a = 0;
    a ^= (ul)std::rand();
    a ^= ((ul)std::rand() << 13);
    a ^= ((ul)std::rand() << 26);
    a ^= ((ul)std::rand() << 38);
    a ^= ((ul)std::rand() << 51);
    return a;
}

typedef uint64_t ul;
double fast_pow(const double a,const float n){
    ul b = *(ul*)&a;
    b *= n;
    return *(double*)&b;
}
/*
int main(){
    std::srand((unsigned)time(0));
    ul t = rand64();
    double a = *(double*)&t;
    std::cout << a << '\n';

    double r1 = std::pow(a,0.5);
    double r2 = fast_pow(a,0.5);

    std::cout << r1 << ' ' << r2 << '/n';
}
 */

int f(){
    return true ^ 5;
}

int main(){
    std::cout <<  f();
}