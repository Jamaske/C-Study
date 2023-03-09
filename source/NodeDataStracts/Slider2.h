#pragma once
#include "Node2.h"

template<typename DT>
struct Slider2{
    Node2<DT>* ptr;

    Slider2(Node2<DT>* node);

    void move(DT n);
    //сдвигает слайдер на n позиций по набору узлов.
    //положительные значения двигают "вправо", отрицательные "влево"
    void insert(Node2<DT>* node);

    Node2<DT>* cut();
    DT get();
};

#include "Slider2.tpp"