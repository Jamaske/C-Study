#include <iostream>

using namespace std;

template <typename arrel>
void BubbleSort(arrel* arr, int n, short size, bool (*comparator)(arrel, arrel, short) = nullptr){
    arrel temp;
    if (comparator == nullptr) {
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
    else{
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - 1; ++j) {
                if ( comparator( arr[j], arr[j + 1], size) ) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

bool distFromCenter(short *a, short *b, short size){
    return abs(a[0] - size/2)+ abs(a[1] - size/2) < abs(b[0] - size/2) + abs(b[1] - size/2);
}

int main(){
    short size, size2;
    cin >> size;
    size2 = size * size;
    short int *solders = new short int[size2];
    for(int i = 0; i < size2; i++){
        cin >> solders[i];
    }

    //сортируем мужиков по росту
    BubbleSort(solders, size2, size);

    short int **placement = new short int *[size2];
    short i, j;
    for(i = 0; i < size; i++){
        for (j = 0; j < size; ++j) {
            placement[i * size + j] = new short[2];
            placement[i * size + j][0] = j;
            placement[i * size + j][1] = i;
        }
    }

    //сортируем все возможные позиции по удалению от центра
    BubbleSort(placement, size2, size, distFromCenter);


    //создаём и двухмерный массив с мужиками
    short **ans = new short *[size];
    for(i = 0; i < size; i++) ans[i] = new short[size];
    for(i = 0; i < size2; i++){
        ans[ placement[i][0] ][ placement[i][1] ] = solders[i];
    }

    //вывод в терминал
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            cout << ans[i][j] << ' ';
        }
        cout << endl;
    }

}