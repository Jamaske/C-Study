#include <iostream>
class A{
public:
    int n = 5;
    int a = 1;
    void factorial();
};

void A::factorial() {
    if(!n) return;
    a *= n;
    --n;
    factorial();
}

void factorial();
int a = 1;
int n = 5;

int main(){
    A obj;
    obj.factorial();
    std::cout << obj.a << '\n';

    factorial();
    std::cout << a << '\n';
}

void factorial(){
    if(!n) return;
    a *= n;
    --n;
    factorial();
}