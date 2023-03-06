#include <iostream>
#include <vector>

using namespace std;

// Пример таблицы смежности
int adj_matrix[4][4] = {{0, 1, 1, 0},
                        {1, 0, 0, 1},
                        {1, 0, 0, 1},
                        {0, 1, 1, 0}};

// Конвертация таблицы смежности
int adj_list[4][4];
for (int i = 0; i < 4; i++) {
for (int j = 0; j < 4; j++) {
if (adj_matrix[i][j] == 1) {
adj_list[i].push_back(j);
}
}
}

// Вывод полученного массива массивов на экран
for (int i = 0; i < 4; i++) {
cout << "Список вершин смежных с вершиной " << i << ": ";
for (int j = 0; j < adj_list[i].size(); j++) {
cout << adj_list[i][j] << " ";
}
cout << endl;
}
