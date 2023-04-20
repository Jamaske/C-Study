#include <iostream>
#include <stack>
typedef uint8_t uc;
typedef uint16_t us;
typedef uint_fast16_t usf;
const us STOPS = 10000;



int main(){
    usf N, M;
    std::cin >> N;

    bool** AdjMtr = new bool*[STOPS];
    for(usf i = 0; i < STOPS; ++i){
        AdjMtr[i] = new bool[STOPS] {false};
    }

    uc prev, cur;
    for(usf i = 0; i < N; ++i){
        std::cin>> M >> prev;
        for(usf j = 0; j < M; ++j){
            std::cin >> cur;
            AdjMtr[cur][prev] = true;
            prev = cur;
        }
    }

    //нанём маршрут с точки prev, что осталась с прошлого этапа

    std::stack<us> recursion;
    std::stack<us>
    for(usf i = 0 )


}