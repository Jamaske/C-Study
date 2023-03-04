#include "Slider1.h"

Slider1::Slider1(Node1* ptr){
    Slider1::ptr = ptr;
}

void Slider1::move(unsigned n){
    while(n--) Slider1::ptr = Slider1::ptr->link;
}

void Slider1::insert(Node1* node){
    node->link = Slider1::ptr->link;
    Slider1::ptr->link = node;
}

Node1* Slider1::cut(){
    Node1* value = Slider1::ptr->link;
    Slider1::ptr->link = value->link;
    return value;
}
