template<typename DT>
Slider2<DT>::Slider2(Node2<DT>* node) {
    Slider2<DT>::ptr = node;
}

template<typename DT>
void Slider2<DT>::insert(Node2<DT>* node){
    node->Rlink = Slider2<DT>::ptr;
    node->Llink = Slider2<DT>::ptr->Llink;
    if(Slider2<DT>::ptr->Llink != nullptr) Slider2<DT>::ptr->Llink->Rlink = node;
    Slider2<DT>::ptr = Slider2<DT>::ptr->Llink = node;
}

template<typename DT>
Node2<DT>* Slider2<DT>::cut(){
    Node2<DT>* tmp = Slider2<DT>::ptr;
    Slider2<DT>::ptr = Slider2<DT>::ptr->Rlink;
    if(tmp->Llink != nullptr) tmp->Llink->Rlink = Slider2<DT>::ptr;
    Slider2<DT>::ptr->Llink = tmp->Llink;
    return tmp;

}

template<typename DT>
DT Slider2<DT>::get(){
    return Slider2<DT>::ptr->data;
}

template<typename DT>
void Slider2<DT>::move(DT n) {
    while(n > 0 && Slider2<DT>::ptr->Rlink != nullptr) {
        Slider2<DT>::ptr = Slider2<DT>::ptr->Rlink;
        n--;
    }
    while (n < 0 && Slider2<DT>::ptr->Llink != nullptr) {
        Slider2<DT>::ptr = Slider2<DT>::ptr->Llink;
        n++;
    }
 }