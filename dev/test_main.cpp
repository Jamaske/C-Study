#include <iostream>
#include "../source/NodeDataStracts/Queue.h"
#include "../source/NodeDataStracts/Stack.h"

int main(){
    Queue<int> num_queue;
    num_queue.push(5);
    std::cout << num_queue.pop() << std::endl;
/*    Node1<char> node1('f');
    std::cout << node1.data;
    Slider1 sld(&node1);


    Node1 node2('r');
    sld.insert(&node2);
    sld.move(1);
    std::cout << sld.ptr->data;*/
}

