#pragma once
#include <iostream>
#include "BitSet.h"
//template<typename NodeIndexType, NodeIndexType, >

class A{
public:
    const int_fast16_t flags;
    //graph state flags
    //all graph fetchers
    //1 - if graph not directional
    //2 - if graph is connected
    //4 - if graph has no cycles
    //specific graph fetchers
    //8 - for  amount of
    //8 - if there is
    const size_t vertices;
    void add_edge(size_t from, size_t to, uint64_t weight);
    void remove_edge(size_t from, size_t to, );
};

class B : virtual A{
    void add() {std::cout << "addition\n";}
    int b;
};

