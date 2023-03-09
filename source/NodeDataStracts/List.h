#pragma once
#include "Slider2.h"

template<typename DT>
struct List{


    List();

    void push(DT el, int idx);//push the element into list at the index

    DT pop(int idx);

    DT get(int idx);

    void replace(int src, int dir);//move element with index src to index dir

    void swap(int idx1, int idx2);

private:
    Node2<DT>* start_node;
    Node2<DT>* end_node;
    Slider2<DT>* slider;
    unsigned sld_idx;
    unsigned len;

    Slider2<DT>* Index_traverse(int idx);
    //flg is bool that represent if sld_idx can be affected



    //void swap()
};