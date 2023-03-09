#include "List.h"

template<typename DT>
List<DT>::List(){
    Node2<DT>* base_node = new Node2<DT>(0);
    start_node = end_node = base_node;
    slider = new Slider2<DT>(base_node);
    len = 0;
    sld_idx = 0;
}

template<typename DT>
Slider2<DT>* List<DT>::Index_traverse(int idx){
    if(idx > List<DT>::len || List<DT>::len + idx < 0) return nullptr;
    if (idx < 0) idx = len + idx;

    if(idx > List<DT>::sld_idx){//right to mobile slider?
        if(len + sld_idx >= (idx << 1)){//closer to slider?
            List<DT>::slider->move(idx - List<DT>::sld_idx);
        }
        else{
            List<DT>::slider->ptr = List<DT>::end_node;
            List<DT>::slider->move(idx - len);
        }
    }
    else{
        if((idx<<1) >= sld_idx){//closer to mob?
            List<DT>::slider->move(idx - List<DT>::sld_idx);
        }
        else{
            List<DT>::slider->ptr = List<DT>::start_node;
            List<DT>::slider->move(idx);
        }
    }
    List<DT>::sld_idx = idx;
    return List<DT>::slider;
}

template<typename DT>
void List<DT>::push(DT el, int idx){
    Index_traverse(idx)->insert(new Node2<DT>(el));
    List<DT>::len++;
    if(idx==0) List<DT>::start_node = List<DT>::start_node->Llink;
}

template<typename DT>
DT List<DT>::pop(int idx){
    Node2<DT>* tmp = Index_traverse(idx)->cut();
    List<DT>::len--;
    DT value = tmp->data;
    delete tmp;
    return value;
}

template<typename DT>
DT List<DT>::get(int idx){
    return Index_traverse(idx)->get();
}

template<typename DT>
void List<DT>::replace(int src, int dir) {
    Node2<DT>* tmp = Index_traverse(src)->cut();
    Index_traverse(dir)->insert(tmp);
}

template<typename DT>
void List<DT>::swap(int idx1, int idx2) {
    int left, right;
    (idx1 > idx2)? (left = idx2, right = idx1):(left = idx1, right = idx2);
    //left = idx1, right = idx2;
    Node2<DT>* tmp = Index_traverse(right)->cut();
    Node2<DT>* shortcut = tmp->Rlink;
    Index_traverse(left)->insert(tmp);
    if(!left) List<DT>::start_node = List<DT>::start_node->Llink;
    List<DT>::slider->move(1);
    List<DT>::sld_idx++;
    tmp = List<DT>::slider->cut();
    List<DT>::slider->ptr = shortcut;
    List<DT>::slider->insert(tmp);
}


