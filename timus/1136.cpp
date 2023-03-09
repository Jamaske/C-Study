#include <iostream>

template<typename DT>
struct Node2{
    DT data;
    Node2<DT>* Rlink;
    Node2<DT>* Llink;

    Node2(DT el);
};

template <typename DT>
Node2<DT>::Node2(DT el){
    Node2<DT>::data = el;
    Node2<DT>::Rlink = nullptr;
    Node2<DT>::Llink = nullptr;
}

template<typename DT>
struct BinTree {
    Node2<DT> *root = nullptr;

    void Rprint(Node2<DT>* node);
    void add(DT el);
    void add_to_subTree(DT el, Node2<DT> *&sub_root);
};

template<typename DT>
void BinTree<DT>::Rprint(Node2<DT> *node) {
    if (node!=nullptr) { //Пока не встретится пустой узел
        Rprint(node->Rlink); //Рекурсивная функция для правого поддерева
        Rprint(node->Llink); //Рекурсивная функция для левого поддерева
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


int main() {
    int size;
    std::cin >> size;
    BinTree<int> tree;
    int * Array = new int[size];

    for (int i = 0; i < size; ++i) {
        std::cin >> Array[i];
    }

    for (int i = size-1; i >= 0; i--) {
        tree.add(Array[i]);
    }

    tree.Rprint(tree.root);

    return 0;
}

