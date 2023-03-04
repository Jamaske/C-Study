#include "List.h"

List::List(){
    Node2* base_node = new Node2(0);
    start_node = end_node = base_node;
    slider = new Slider2(base_node);
    len = 0;
    sld_idx = 0;
}

Slider2* List::Index_traverse(int idx){
    if(idx > List::len || List::len + idx < 0) return nullptr;
    if (idx < 0) idx = len + idx;

    if(idx > List::sld_idx){//right to mobile slider?
        if(len + sld_idx >= (idx << 1)){//closer to slider?
            List::slider->move(idx - List::sld_idx);
        }
        else{
            List::slider->ptr = List::end_node;
            List::slider->move(idx - len);
        }
    }
    else{
        if((idx<<1) >= sld_idx){//closer to mob?
            List::slider->move(idx - List::sld_idx);
        }
        else{
            List::slider->ptr = List::start_node;
            List::slider->move(idx);
        }
    }
    List::sld_idx = idx;
    return List::slider;
}

void List::push(int el, int idx){
    Index_traverse(idx)->insert(new Node2(el));
    List::len++;
    if(idx==0) List::start_node = List::start_node->Llink;
}

int List::pop(int idx){
    Node2* tmp = Index_traverse(idx)->cut();
    List::len--;
    int value = tmp->data;
    delete tmp;
    return value;
}

int List::get(int idx){
    return Index_traverse(idx)->get();
}

void List::replace(int src, int dir) {
    Node2* tmp = Index_traverse(src)->cut();
    Index_traverse(dir)->insert(tmp);
}

void List::swap(int idx1, int idx2) {
    int left, right;
    (idx1 > idx2)? (left = idx2, right = idx1):(left = idx1, right = idx2);
    //left = idx1, right = idx2;
    Node2* tmp = Index_traverse(right)->cut();
    Node2* shortcut = tmp->Rlink;
    Index_traverse(left)->insert(tmp);
    if(left==0) List::start_node = List::start_node->Llink;
    List::slider->move(1);
    List::sld_idx++;
    tmp = List::slider->cut();
    List::slider->ptr = shortcut;
    List::slider->insert(tmp);
}


