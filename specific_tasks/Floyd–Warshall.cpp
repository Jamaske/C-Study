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
    std::vector<std::vector<WT>> Distance;// в итоге будет хранить длины кротчайших путей между любыми двумя вершинами (даже если ребра напрямую между ними нет)
    std::vector<std::vector<NT>> sequent;// нужен если хочется после легко восстановить любой путь
    std::vector<std::vector<NT>> penultimate;// этот же для восстановления пути в обратном порядке
    explicit Graph(std::ifstream& file);//ввод матрицы из потока
    void optimize_dist();//сам алгоритм
    void print_dists();
    void print_path_between(NT start, NT destination);// использует sequent дял вывода пути за линию от количества вершин в пути
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
                    sequent[i][j] = sequent[i][k];
                }
            }
        }

// пояснение алгоритма:

// На начало k-ой итерации первого цикла, для какой-то пары вершин (i, j)
// смысл значения Dist[i][j] можно объяснить как:
// если бы у нас был граф с вершинами {i, j, 1, 2,.., k-2, k-1}
// и на нём, среди всех путей между (i->j), мы знали самый короткий.
// Его длинна и хранится в Dist[i][j] после k-1 итерации.
// После же решили добавить новую вершину, под номером k и рёбра её связывающие.
// Появились новые путей между (i, j), проходящие через добавленную вершину (i->k->j).
// Хочется узнать будет ли какой-то из новых путей, короче, чем лучший до добавления k.
// Чтобы не сравнивать с каждым, сперва найдём кротчайший из ново добавленных и сравним только с ним.
// Поскольку все новые пути проходят через k, их можно разделять на две части: (i->k) и (k->j)
// Самый короткий путь (i->j) через k это склейка кротчайшего (i->k) и кротчайшего (k->j),
    // причём допустим, что в этом пути (i->k) будет содержать вершина j, то склейка его с любым путём (k->j)
    // образует путь (i->j->k->j) который можно разбить на части (i->j) и (j->k->j)
    // получим, что внутри есть цикл, а по условию применимости алгоритма в графе не должно быть отрицательных циклов,
    // потому часть пути (i->j) будет корчем чем он целиком. Поэтому в этом случае если кротчайший (i->k) содержит j или
    // кротчайший (k->j) содержит i, самый короткий (i->k->j) не будет короче предыдущего лучшего (i->j).
// Поэтому при поиске кротчайших (i->k) и (k->j) достаточно рассматривать пути на графах
// {i, k, 1, 2,.., k-2, k-1} и {k, j, 1, 2,.., k-2, k-1} соответственно, а не на {i, j, k, 1, 2,.., k-2, k-1} целиком.
// Эти задачи уже были решены на итерации k-1 в ячейках Dist[i][k] и Dist[k][j]
// после сравнения мы узнаем кротчайший путь (i->j) на графе {i, j, 1, 2,.., k-1, k} и сможем перейти к следующий итерации
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