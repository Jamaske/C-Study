#include <iostream>
#include <cmath>
typedef uint64_t ui;
#define debug false

int main(){
    ui N, W; //N - cubes amount, W - stairs width
    std::cin >> N;
    ui max_width = ((ui)std::sqrt(8 * N + 1) - 1) >> 1;//sqrt(2*N+0.5) - 0.5
    ui** arr = new ui* [N];
    arr[0] = new ui[max_width] {0}; arr[0][0] = 1;//инициализируем первую строку нулями и единицей в начале
    for(ui i = 1; i < N; ++i){
        arr[i] = new ui[max_width] {1};//инициализируем первый столбик единицами
    }

    ui prev_N;
    for (ui i = 1; i < N; ++i){
        for (ui j = 1; j < max_width; ++j){
            if(i > j){
            arr[i][j] = arr[i - j - 1][j] + arr[i - j - 1][j - 1];
            }
            else{
                arr[i][j] = 0;
            }
        }
    }
#if debug
    for (ui i = 0; i < N; ++i){
        for (ui j = 0; j < max_width; ++j){
            std::cout << arr[i][j] << '\t';
        }
        std::cout  << '\n';
    }
#endif
    ui total_combinations = 0;
    for(ui i = 1; i < max_width; ++i){
        total_combinations += arr[N - 1][i];
    }
    std::cout << total_combinations << '\n';

}