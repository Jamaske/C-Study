#pragma once
#include "Slider1.h"

template<typename DT>
struct Stack{
    //одно-направленная цепь из узлов
    Slider1<DT>* top_sld;

    Stack();
    Node1<DT>* get_top_Node();
    bool not_empty();

    DT pop();
    void push(DT el);

};

#include "Stack.tpp"