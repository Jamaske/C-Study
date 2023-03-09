#pragma once
#include "Node1.h"

template<typename DT>
struct Slider1{
    //объект перемещаемый по одно-направленной цепочке
    Node1<DT>* ptr;

    Slider1(Node1<DT>* node);

    void move(unsigned n = 1);
    //сдвигает слайдер на n позиций по направлению цепочки
    void insert(Node1<DT>*);
    //вставляет узел в цепочку перед ptr
    Node1<DT>* cut();
    //вырезает из цепочки узел перед ptr

};

#include "Slider1.tpp"