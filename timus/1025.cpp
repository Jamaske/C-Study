#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


int main(){
    int grop, sum=0;
    string s;
    cin >> grop;
    int *arr = new int[grop];
    for(int i  = 0; i < grop; i++){
        cin >> s;
        arr[i] = stoi(s);
    }
    sort(arr,arr+ grop);


    for(int i = 0; i*2 < grop ; i++){
        sum += (arr[i]+1)/2;
    }
    cout << sum;
}