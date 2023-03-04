#pragma once
#include "Node2.h"

struct Slider2{
    Node2* ptr;

    Slider2(Node2* node);

    void move(int n);
    //сдвигает слайдер на n позиций по набору узлов.
    //положительные значения двигают "вправо", отрицательные "влево"
    void insert(Node2* node);

    Node2* cut();
    int get();

};