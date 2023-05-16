#include <iostream>
typedef unsigned int ui;

int main(){
    ui n = 10, k = 4;
    int* base = new int[n];
    for(ui i = 0; i < n; ++i){
        base[i] = i;
    }

    int* source = new int[k];
    for(ui i = 0; i < k; ++i){
        source[i] = i;
    }

    ui diff = n - k;
    while(true){

        ui to_move = k - 1;
        if(source[to_move] == n - 1) --to_move;
        while(source[to_move] == n - )
    }
}