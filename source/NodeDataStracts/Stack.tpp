template<typename DT>
Stack<DT>::Stack(){
    Node1<DT>* base_node = new Node1<DT>(0);
    Stack<DT>::top_sld = new Slider1<DT>(base_node);
}

template<typename DT>
Node1<DT>* Stack<DT>::get_top_Node(){
    return Stack<DT>::top_sld->ptr->link;
}

template<typename DT>
bool Stack<DT>::not_empty() {
    return Stack<DT>::get_top_Node() != nullptr;
}

template<typename DT>
DT Stack<DT>::peek(){
    return get_top_Node()->data;
}

template<typename DT>
DT Stack<DT>::pop(){
    Node1<DT>* tmp = Stack<DT>::top_sld->cut();
    DT value = tmp->data;
    delete tmp;
    return value;
}

template<typename DT>
void Stack<DT>::push(DT el){
    Node1<DT>* new_node = new Node1(el);
    Stack::top_sld->insert(new_node);
}