#include<iostream>
#include <list>
#include <stack>

// Класс для представления графа
class graph
{
    int V;	// Количество вершин

    //  Указатель на массив, содержащий список смежности
    std::list<int> *adj;

    // Функция, используемая topologicalSort
    void topologicalSortUtil(int v, bool visited[], std::stack<int> &Stack);
public:
    graph(int V);   // Конструктор

    // Функция для добавления ребра в граф
    void addEdge(int v, int w);

    // Выводит топологическую сортировку графа
    void topologicalSort();

    void print();
};

graph::graph(int V)
{
    this->V = V;
    adj = new std::list<int>[V];
}

void graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

// Рекурсивная функция, используемая topologicalSort
void graph::topologicalSortUtil(int v, bool visited[], std::stack<int> &Stack)
{
    // Помечаем текущий узел как посещенный
    visited[v] = true;

    // Рекурсивно вызываем функцию для всех смежных вершин
    std::list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);

    // Добавляем текущую вершину в стек с результатом
    Stack.push(v);
}

// Функция для поиска топологической сортировки.
// Рекурсивно использует topologicalSortUtil()
void graph::topologicalSort()
{
    std::stack<int> Stack;

    // Помечаем все вершины как непосещенные
    bool *visited = new bool[V];
    for (int i = 1; i < V; i++)
        visited[i] = false;

    // Вызываем рекурсивную вспомогательную функцию
    // для поиска топологической сортировки для каждой вершины
    for (int i = 1; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

    // Выводим содержимое стека
    while (Stack.empty() == false)
    {
        std::cout << Stack.top() << " ";
        Stack.pop();
    }
}

void graph::print() {
    for (int i = 1; i < V; i++)
    {
        for (int v: this->adj[i]) {
            std::cout << "(" << i << ", " << v  << ") ";
        }
        std::cout << std::endl;
    }
}




int main()
{

    int Size;
    std::cin>>Size;

    graph g(Size+1);

    int Cur;
    for (int i = 1; i <= Size; ++i) {
        std::cin>>Cur;
        while(Cur!=0){
            g.addEdge(i,Cur);
            std::cin>>Cur;
        }

    }

    //g.print();

    g.topologicalSort();

    return 0;
}