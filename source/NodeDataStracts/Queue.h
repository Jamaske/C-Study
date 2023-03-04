#pragma once
#include "Slider1.h"

struct Queue{
    //одно-направленная цепь из узлов
    Slider1* start_sld;
    Slider1* end_sld;

    Queue();
    Node1* get_start_Node();
    Node1* get_end_Node();

    bool not_empty();
    int pop();
    void push(int el);
};