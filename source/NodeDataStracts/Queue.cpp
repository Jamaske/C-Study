#include "Queue.h"


Queue::Queue(){
    Node1* base_node = new Node1(228);
    Queue::start_sld = new Slider1(base_node);
    Queue::end_sld = new Slider1(base_node);
}

Node1* Queue::get_start_Node(){
    return Queue::start_sld->ptr->link;
}

Node1* Queue::get_end_Node() {
    return Queue::end_sld->ptr;
}

bool Queue::not_empty() {
    return Queue::get_start_Node() != nullptr;
}

int Queue::pop(){
    Node1* tmp = Queue::start_sld->cut();
    int value = tmp->data;
    delete tmp;
    return value;
}

void Queue::push(int el){
    Node1* new_node = new Node1(el);
    Queue::end_sld->insert(new_node);
    Queue::end_sld->move();
}
