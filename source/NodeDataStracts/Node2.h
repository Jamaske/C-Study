#pragma once

template<typename DT>
struct Node2{
    DT data;
    Node2<DT>* Rlink;
    Node2<DT>* Llink;

    Node2(DT el);
};

#include "Node2.tpp"