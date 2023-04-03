#include <iostream>
#include <iomanip>




class A{
public:
    static int f;
    int operator[](int a){
        return a << 2;
    }
    int operator()(int idx1, int idx2){
        return  idx1 + idx2;
    }
};

int A::f;

int main(){
    A::f = 5;
    int a = 203;
    A obj;
    std::cout << obj[5];
}
