#include <iostream>

typedef uint32_t ui;

int main(){
    ui N;
    std::cin >> N;
    //ui* cost = new ui[N]{0};//volume = idx + 1;   max_volume = N
    ui cost[11]{0};

    ui I;
    std::cin >> I;
    ui volume;
    for(ui i = 0; i < I; ++i){
        std::cin >> volume;
        if(volume <= N)
            std::cin >> cost[volume];
    }

    ui new_set_cost;
    for (ui i = 2; i < N+1; ++i){
        for (ui j = 1; j <= (i>>1); ++j){
            new_set_cost = cost[j] + cost[i - j];
            if(new_set_cost > cost[i])
                cost[i] = new_set_cost;

        }
    }
    std::cout << cost[N];



}