#pragma once

template<typename DT>//DT - Data Type
struct Node1{
    //односвязный узел/звено хранения
    DT data;
    Node1<DT>* link;
    Node1(DT el);
};

#include "Node1.tpp"

