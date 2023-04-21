#include <iostream>
#include <stack>
#include <set>
#include <vector>
typedef uint16_t us;
typedef uint_fast16_t usf;
const us STOPS = 10000;



void eler(std::vector<std::set<us>>& AdjList, us start, std::stack<us>& revans){
    std::stack<us> recursion;
    recursion.push(start);
    us top;
    us next;
    while (!recursion.empty()){//пока стек не пуст
        top = recursion.top();
        if(AdjList[top].empty()){
            revans.push(top);
            recursion.pop();
        }
        else{
            next = *AdjList[top].begin();
            recursion.push(next);
            AdjList[top].erase(next);
        }
    }
}



int main(){

    usf N, M;
    std::cin >> N;

    std::vector<std::set<us>> AdjList(1000);

    us prev, cur;
    for(usf i = 0; i < N; ++i){
        std::cin>> M >> prev;
        for(usf j = 0; j < M; ++j){
            std::cin >> cur;
            AdjList[prev-1].insert(cur-1);
            prev = cur;
        }
    }

    //нанём маршрут с точки prev, что осталась с прошлого этапа


    std::stack<us> reversed_answer;
    eler(AdjList, prev-1, reversed_answer);

    std::cout << reversed_answer.size() -1  << ' ' ;
    while (!reversed_answer.empty()){
        std::cout << reversed_answer.top() + 1 << ' ';
        reversed_answer.pop();
    }

}