#pragma once
#include "Node2.h"

template<typename DT>
struct BinTree {
    Node2<DT> *root = nullptr;

    void Rprint(Node2<DT>* node);
    void add(DT el);
    void add_to_subTree(DT el, Node2<DT> *&sub_root);
};

#include "BinTree.tpp"