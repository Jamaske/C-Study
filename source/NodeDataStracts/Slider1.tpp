
template<typename DT>
Slider1<DT>::Slider1(Node1<DT>* ptr){
    Slider1<DT>::ptr = ptr;
}

template<typename DT>
void Slider1<DT>::move(unsigned n){
    while(n--) Slider1<DT>::ptr = Slider1<DT>::ptr->link;
}

template<typename DT>
void Slider1<DT>::insert(Node1<DT>* node){
    node->link = Slider1<DT>::ptr->link;
    Slider1<DT>::ptr->link = node;
}

template<typename DT>
Node1<DT>* Slider1<DT>::cut(){
    Node1<DT>* value = Slider1<DT>::ptr->link;
    Slider1<DT>::ptr->link = value->link;
    return value;
}
