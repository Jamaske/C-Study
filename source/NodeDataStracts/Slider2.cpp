#include "Slider2.h"

Slider2::Slider2(Node2* node) {
    Slider2::ptr = node;
}

void Slider2::insert(Node2* node){
    node->Rlink = Slider2::ptr;
    node->Llink = Slider2::ptr->Llink;
    if(Slider2::ptr->Llink != nullptr) Slider2::ptr->Llink->Rlink = node;
    Slider2::ptr = Slider2::ptr->Llink = node;
}

Node2* Slider2::cut(){
    Node2* tmp = Slider2::ptr;
    Slider2::ptr = Slider2::ptr->Rlink;
    if(tmp->Llink != nullptr) tmp->Llink->Rlink = Slider2::ptr;
    Slider2::ptr->Llink = tmp->Llink;
    return tmp;

}

int Slider2::get(){
    return Slider2::ptr->data;
}

void Slider2::move(int n) {
    while(n > 0 && Slider2::ptr->Rlink != nullptr) {
        Slider2::ptr = Slider2::ptr->Rlink;
        n--;
    }
    while (n < 0 && Slider2::ptr->Llink != nullptr) {
        Slider2::ptr = Slider2::ptr->Llink;
        n++;
    }
 }