#pragma once
#include "Slider1.h"

template<typename DT>
struct Queue{
    //одно-направленная цепь из узлов
    Slider1<DT>* start_sld;
    Slider1<DT>* end_sld;

    Queue();
    Node1<DT>* get_start_Node();
    Node1<DT>* get_end_Node();

    bool not_empty();
    DT pop();
    void push(DT el);
};

#include "Queue.tpp"