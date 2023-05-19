#include <iostream>
typedef unsigned int ui;

class A{
public:
    int pub;
private:
    int riv;
protected:
    int prot;
public:
    A(int a){
        std::cout << "A2 constructor\n";
    }

    A(){
        std::cout << "A constructor\n";
    }
    ~A(){
        std::cout << "A destructor\n";
    }
};

class B:A{
public:
    B(){
        std::cout << "B constructor\n";
    }
    ~B(){
        std::cout << "B destructor\n";
    }
};


int main(){
    B b;
}