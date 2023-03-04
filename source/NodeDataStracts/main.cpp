#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "2stack-queue.h"
#include "List.h"

#include <queue>


int main() {

    List *list = new List();
    const int n = 10;
    int a[n] = {6, 7, 3, 1, 9, 2, 8, 0, 4, 5};

    for (int i = 0; i < n; i++) {
        list->push(a[i], i);
    }

    for (int i = n - 1; i; i--) {
        for (int j = 0; j < i; j++) {
            if (list->get(j) > list->get(j + 1)) {
                list->swap(j, j + 1);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        std::cout << list->get(i);
    }


}
