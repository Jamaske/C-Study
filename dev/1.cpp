#include <iostream>
#include<vector>
#include <fstream>

typedef unsigned int NT;
typedef int WT;
#define INF 1000;

class Graph{
public:
    int N;
    std::vector<std::vector<WT>> Dists;
    std::vector<std::vector<NT>> Next;
    Graph(std::ifstream& read);
    void optimize_dist();
    void print_dists();
    void print_path_between(int);
};

Graph::Graph(std::ifstream& inp) {
    inp >> N;
    WT cur;
    Dists.resize(N);
    Next.resize(N);
    for(NT i = 0 ; i < N; ++i){
        Dists[i].resize(N);
        Next[i].resize(N);
        for(NT j = 0; j < N; ++j){
            inp >> cur;
            Dists[i][j] = cur;
            Next[i][j] = j;
        }
        Next[i][i] = 0;
    }
}

void Graph::optimize_dist() {
    NT alternative;
    for (NT k = 0; k < N ; ++k) {
        for (NT i = 0; i < N; ++i) {
            for (NT j = 0; j < N; ++j) {
                alternative = Dists[i][k] + Dists[k][j];
                if (Dists[i][j] > alternative){
                    Dists[i][j] = alternative;

                }
            }
        }
    }
}

void Graph::print_dists() {
    for(NT i = 0; i < N; ++i){
        for(NT j = 0; j < N; ++j){
            std::cout << Dists[i][j] << ' ';
        }
        std::cout << '\n';

    }
}

int main(){
    std::ifstream file("C:\\Users\\ptax\\data\\scripts\\C++\\dev\\inp.txt");
    std::cout << file.is_open() << '\n';
    Graph graph (file);
    graph.print_dists();



}