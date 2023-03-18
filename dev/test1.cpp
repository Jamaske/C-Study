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


using namespace std;
int main(){



}