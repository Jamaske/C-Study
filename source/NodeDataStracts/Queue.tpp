template<typename DT>
Queue<DT>::Queue(){
    Node1<DT>* base_node = new Node1<DT>(0);
    Queue<DT>::start_sld = new Slider1<DT>(base_node);
    Queue<DT>::end_sld = new Slider1<DT>(base_node);
}

template<typename DT>
Node1<DT>* Queue<DT>::get_start_Node(){
    return Queue<DT>::start_sld->ptr->link;
}

template<typename DT>
Node1<DT>* Queue<DT>::get_end_Node() {
    return Queue<DT>::end_sld->ptr;
}

template<typename DT>
bool Queue<DT>::not_empty() {
    return Queue<DT>::get_start_Node() != nullptr;
}

template<typename DT>
DT Queue<DT>::pop(){
    Node1<DT>* tmp = Queue<DT>::start_sld->cut();
    DT value = tmp->data;
    delete tmp;
    return value;
}

template<typename DT>
void Queue<DT>::push(DT el){
    Node1<DT>* new_node = new Node1(el);
    Queue<DT>::end_sld->insert(new_node);
    Queue<DT>::end_sld->move();
}
