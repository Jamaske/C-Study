#include <iostream>
#include<vector>
#include <fstream>
#define debug false
typedef unsigned int NT;
typedef int WT;
#define INF 1000;

const char* path = "C:\\Users\\User\\data\\my_scripts\\C++\\dev\\inp2.txt";

class Graph{
public:
    int Vert_Number;
    std::vector<std::vector<WT>> Distance;
    std::vector<std::vector<NT>> sequent;
    std::vector<std::vector<NT>> penultimate;
    explicit Graph(std::ifstream& file);
    void optimize_dist();
    void print_dists();
    void print_path_between(NT start, NT destination);
    void print_reversed_path_between(NT start, NT destination);
};

Graph::Graph(std::ifstream& file): Vert_Number() {
    file >> Vert_Number;
    WT cur;
    Distance.resize(Vert_Number);
    sequent.resize(Vert_Number);
    penultimate.resize(Vert_Number);
    for(NT i = 0 ; i < Vert_Number; ++i){
        Distance[i].resize(Vert_Number);
        sequent[i].resize(Vert_Number);
        penultimate[i].resize(Vert_Number);
        for(NT j = 0; j < Vert_Number; ++j){
            file >> cur;
            Distance[i][j] = cur;
            sequent[i][j] = j;
            penultimate[i][j] = i;
        }
    }
}

void Graph::optimize_dist() {
    WT alternative_path_length;
    for (NT k = 0; k < Vert_Number ; ++k) {
        for (NT i = 0; i < Vert_Number; ++i) {
            for (NT j = 0; j < Vert_Number; ++j) {
                alternative_path_length = Distance[i][k] + Distance[k][j];
                if (Distance[i][j] > alternative_path_length){
                    Distance[i][j] = alternative_path_length;
                    penultimate[i][j] = penultimate[k][j];
                    sequent[i][j] = sequent[i][k];//parent

                }
            }
        }
#if debug
        std::cout << "\nk: "<< k << '\n';
        print_dists();
#endif
    }
}

void Graph::print_dists() {
    std::cout << "distance\n";
    for(NT i = 0; i < Vert_Number; ++i){
        for(NT j = 0; j < Vert_Number; ++j){
            std::cout << Distance[i][j] << '\t';
        }
        std::cout << '\n';

    }
#if debug
    std::cout << "\nPre_last\n";
    for(NT i = 0; i < Vert_Number; ++i){
        for(NT j = 0; j < Vert_Number; ++j){
            std::cout << penultimate[i][j] << '\t';
        }
        std::cout << '\n';

    }
    std::cout << "\nNext\n";
    for(NT i = 0; i < Vert_Number; ++i){
        for(NT j = 0; j < Vert_Number; ++j){
            std::cout << sequent[i][j] << '\t';
        }
        std::cout << '\n';

    }
#endif
}

void Graph::print_path_between(NT start, NT destination) {
    do{
        std::cout << start << ")->(";
        start = sequent[start][destination];
    } while(start != destination);
    std::cout << start << '\n';
}

void Graph::print_reversed_path_between(NT start, NT destination) {
    do{
        std::cout << destination << ")<-(";
        destination = penultimate[start][destination];
    } while(destination != start);
    std::cout << destination << '\n';
}


int main(){
    std::ifstream file(path);
    Graph graph (file);
    graph.print_dists();
    graph.optimize_dist();
    std::cout << "\n\n";
    graph.print_dists();
    graph.print_path_between(4,3);
    graph.print_reversed_path_between(4,3);



}