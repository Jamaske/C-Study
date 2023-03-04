#pragma once
#include "Slider1.h"

struct Stack{
    //одно-направленная цепь из узлов
    Slider1* top_sld;

    Stack();
    Node1* get_top_Node();
    bool not_empty();

    int pop();
    void push(int el);

};