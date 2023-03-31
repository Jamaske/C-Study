#pragma once









#include <iostream>
//template<typename NodeIndexType, NodeIndexType, >

class A{
    virtual void add() = 0;
    int a;
};

class B : virtual A{
    void add() {std::cout << "addition\n";}
    int b;
};

