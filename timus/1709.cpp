#include <iostream>

typedef unsigned int ui;
typedef unsigned char uc;

struct node{
    uc row,column;
    node* prev;
    node(uc row, uc column):row(row), column(column), prev(nullptr){}
};

struct queue{
    node *base, *last;

    queue(){
        last = base = new node(0,0);
    }

    void push(node* New){
        last = last->prev = New;
    }
    node* pop(){
        node& ret = *(base->prev);
        base->prev = ret.prev;
        return &ret;
    }
    node* peek(){
        return (base->prev);
    }

};

int main(){
    ui n, a, d;
    std::cin >> n >> d >> a;
    ui total_cost = 0;
    uc cur;
    uc *colour_up = new uc[n] {0};
    uc *colour_down = new uc[n] {0};
    uc *colour_cur;
    queue deleteion_queue;
    uc min, max;
    for(ui i = 0; i < n; ++i){
        for(ui j = 0; j < n; ++j){
            std::cin >> cur;
            if(cur!='0'){
                if(i == j) continue;
                if(i < j){
                    colour_cur = colour_up;
                    min = i;
                    max = j;
                }
                else{
                    colour_cur = colour_down;
                    min = j;
                    max = i;
                }
                if(colour_cur[i]){
                    if(colour_cur[j]){//i!=0 and j!=0
                        if(colour_cur[i] == colour_cur[j]){//cycle found need mark this to deletion
                            total_cost += d;
                            deleteion_queue.push(new node(i,j));
                        }
                        else{//bridge found have to recolour one of the nets
                            for(ui k = max-1; k < n; ++k){
                                if(colour_cur[k] == max) colour_cur[k] = min;
                            }
                        }
                    }
                    else{//i!=0 and j==0 share colour
                        colour_cur[j] = colour_cur[i];
                    }
                }
                else{
                    if(colour_cur[j]){//i==0 and j!=0 share colour
                        colour_cur[i] = colour_cur[j];
                    }
                    else{//both equal zero
                        colour_cur[i] = colour_cur[j] = min + 1;
                    }
                }
            }
        }
    }
    total_cost /=2;
    bool *additions = new bool[n]{};
    cur = 1;
    for(ui i = 0; i < n; ++i){
        if(colour_up[i] == 0){
            additions[i] = true;
            total_cost += a;
            continue;
        }
        if(colour_up[i] > cur){
            additions[i] = true;
            total_cost += a;
            cur = colour_up[i];
            continue;
        }
    }

    std::cout << total_cost << '\n';
    node* next = deleteion_queue.peek();
    for(ui i = 0; i < n; ++i){
        for(ui j = 0; j < n; ++j){
            if((!i && additions[j]) || (!j && additions[i])){
                std::cout << 'a';
                continue;
            }
            if(next != nullptr && next->row == i && next->column == j){
                deleteion_queue.pop();
                next = deleteion_queue.peek();
                std::cout << 'd';
                continue;
            }
            std::cout << '0';
        }
        std::cout << '\n';
    }
}