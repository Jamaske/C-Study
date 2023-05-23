#include <iostream>
#include <functional>
#include "PriorQueue.h"

typedef uint64_t ul;
typedef uint32_t ui;

struct node_dist_holder{
    ui node;
    ul dist;
    node_dist_holder(ui node, ul dist):
    node(node), dist(dist){}
    bool operator > (node_dist_holder other) const{
        return dist > other.dist;
    }
};


int main(){
    DynArr<node_dist_holder> a(4);    //PriorQueue<node_dist_holder> queue;




}