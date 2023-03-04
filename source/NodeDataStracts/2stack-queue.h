#pragma once
#include "Stack.h"

struct Queue2{
    Stack* BufferIn;
    Stack* BufferOut;

    Queue2();
    void push(int el);
    int pop();
};