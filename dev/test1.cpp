#include <iostream>
#include "cmath"

template<typename DT>//DT - Data Type DN-Data Number
class Node1{
    //односвязный узел/звено хранения
public:
    DT *data;
    Node1<DT>* link;
    Node1(DT *el);
};


template<typename DT>
Node1<DT>::Node1(DT *el){
    data = el;
    link = nullptr;
}


struct NodeData{
    int num;
    int max;
    int min;

    NodeData(){
        NodeData::num = 0;
        max = INT32_MIN;
        min = INT32_MAX;
    }

    NodeData(int num, NodeData* prev){
        NodeData::num =num;
        max = std::max(num, prev->max);
        min = std::min(num, prev->min);
    }

};

class first {
    int value;

    int get_self(){
        return value;
    }
public:
    first(int value){
        first::value = value;
    }


    template<class T>
    int get_other(T* obj){
        return obj->value;
    }
};


class second {
    int value;

    int get_self(){
        return value;
    }
public:
    second(int value){
        second::value = value;
    }


    template<class T>
    int get_other(T* obj){
        return obj->value;
    }
};


using namespace std;
int main(){
    NodeData::NodeData();
    NodeData* h = new NodeData();
    NodeData k(5,h);

    Node1<NodeData> a(h);
    Node1<NodeData>b(&k);
    std::cout << a.data->max << std::endl;
    a.data->max = 8;
    std::cout << a.data->max << std::endl;
    std::cout << b.data->num << std::endl;
    std::cout << sizeof(a);
    //delete h;
//    first a(1);
//    first b(2);
    //std::cout << a.get_self();
    //std::cout << b.get_other(&a);







}