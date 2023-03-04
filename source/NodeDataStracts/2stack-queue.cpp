#include "2stack-queue.h"

Queue2::Queue2() {
    Queue2::BufferIn = new Stack();
    Queue2::BufferOut = new Stack();
}

void Queue2::push(int el){
    BufferIn->push(el);
}

int Queue2::pop(){
    if(!BufferOut->not_empty()){//если в буффере на вывод кончились данные
        while(BufferIn->not_empty()){//полностью перенести все данные из буффера ввода
            BufferOut->push(BufferIn->pop());
        }
    }

    if(BufferOut->not_empty()){
        return BufferOut->pop();
    }
    else{
        return -1;
    }
}