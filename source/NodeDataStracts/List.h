#pragma once
#include "Slider2.h"

struct List{


    List();

    void push(int el, int idx);//push the element into list at the index

    int pop(int idx);

    int get(int idx);

    void replace(int src, int dir);//move element with index src to index dir

    void swap(int idx1, int idx2);

private:
    Node2* start_node;
    Node2* end_node;
    Slider2* slider;
    unsigned sld_idx;
    unsigned len;

    Slider2* Index_traverse(int idx);
    //flg is bool that represent if sld_idx can be affected



    //void swap()
};