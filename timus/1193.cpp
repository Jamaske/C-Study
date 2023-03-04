#include <iostream>
#include <string>
using namespace std;

void BubbleSort(int**,int*,int);

int main() {
    int n;
    cin >> n;

    int** a= new int * [n];
    int *b = new int[n];
    for (int i = 0; i < n; ++i) {
        a[i] = new int[3];
        b[i] = i;
        for (int j = 0; j < 3; ++j) {
            cin >> a[i][j];
        }
    }

    BubbleSort(a, b, n);

    /*
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << a[b[i]][j] << ' ';
        }
        cout << endl;
    }
    */

    int Difference,TimeOfFreeQueue;
    TimeOfFreeQueue = a[b[0]][0]+a[b[0]][1];
    Difference=-a[b[0]][2]+TimeOfFreeQueue;
    for (int i = 1; i < n; ++i) {
        TimeOfFreeQueue=max(TimeOfFreeQueue,a[b[i]][0])+a[b[i]][1];
        Difference = max(Difference, TimeOfFreeQueue - a[b[i]][2]);

        //cout << TimeOfFreeQueue << endl;
    }

    if(Difference<0) cout << 0 << endl;
    else cout << Difference << endl;



    return 0;
}

void BubbleSort(int** a, int* b, int n){
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (a[ b[j] ][0] > a[b[j + 1]][0]) {
                int temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }
}