#pragma once
#include <iostream>
#include "../source/BitSet.h"
//template<typename NodeIndexType, NodeIndexType, >

class Graph{
public:
    const int_fast16_t flags;
    //graph state flags
    //all graph fetchers
    //1 - if graph directional
    //2 - if graph is connected
    //4 - if graph has no cycles
    //8 - if weighted
    //specific graph fetchers
    //16 - for  amount of
    //8 - if there is
    const size_t vertices;
    Graph(size_t node_count);
    void add_edge(size_t from, size_t to, int64_t weight = 1);
    int64_t remove_edge(size_t from, size_t to);

};

class AjMatGraph: virtual Graph{
    void add() {std::cout << "addition\n";}
    int b;
};

class ArrListGraph: virtual Graph{
    void add_edge()
};

class EdgeGraph: virtual Graph{

};

