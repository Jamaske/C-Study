#pragma once
#include "Node1.h"

struct Slider1{
    //объект перемещаемый по одно-направленной цепочке
    Node1* ptr;

    Slider1(Node1* node);

    void move(unsigned n = 1);
    //сдвигает слайдер на n позиций по направлению цепочки
    void insert(Node1*);
    //вставляет узел в цепочку после ptr
    Node1* cut();
    //вырезает из цепочки узел после ptr

};