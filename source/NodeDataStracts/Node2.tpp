template <typename DT>
Node2<DT>::Node2(DT el){
    Node2<DT>::data = el;
    Node2<DT>::Rlink = nullptr;
    Node2<DT>::Llink = nullptr;
}