#include<iostream>
using namespace std;

int main() {
    int N, N2;
    cin >> N;
    N2 = N * N;
    int *arr = new int[N2];
    for (int i = 0; i < N2; i++) {
        cin >> arr[i];
    }


    for(int i = 0;  i < 2*N-1; i++){
        for(int g = max(0, i-N+1); g < min(i+1, N); g++){
            cout<< arr[N*(i-g)+g]<<" ";
        }
    }

    delete arr;
}