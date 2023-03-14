
#include <iostream>

template<typename DT>
void BinTree<DT>::Rprint(Node2<DT> *node) {
    if (node!=nullptr) {
        Rprint(node->Rlink);
        Rprint(node->Llink);
        std::cout << node->data << std::endl; //Отображаем корень дерева
    }
}

template<typename DT>
void BinTree<DT>::add_to_subTree(DT el, Node2<DT> *&sub_root) {
    if (sub_root == nullptr) { // Если дерева нет, то формируем корень
        sub_root = new Node2<DT>(el); // память под узел
        return;
    }
    if (el < sub_root->data) add_to_subTree(el,sub_root->Llink);
    else add_to_subTree(el,sub_root->Rlink);
}

template<typename DT>
void BinTree<DT>::add(DT el) {
    add_to_subTree(el, root);
}