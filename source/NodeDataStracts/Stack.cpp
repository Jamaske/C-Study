#include "Stack.h"


Stack::Stack(){
    Node1* base_node = new Node1(228);
    Stack::top_sld = new Slider1(base_node);
}

Node1* Stack::get_top_Node(){
    return Stack::top_sld->ptr->link;
}

bool Stack::not_empty() {
    return Stack::get_top_Node() != nullptr;
}

int Stack::pop(){
    Node1* tmp = Stack::top_sld->cut();
    int value = tmp->data;
    delete tmp;
    return value;
}

void Stack::push(int el){
    Node1* new_node = new Node1(el);
    Stack::top_sld->insert(new_node);
}