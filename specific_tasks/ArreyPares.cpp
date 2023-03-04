#include<iostream>
using namespace std;

void swap(int arr[],unsigned int i,unsigned int g){
    int temp = arr[i];
    arr[i] = arr[g];
    arr[g] = temp;
}


void quicksort(int arr[], int end, int start = 0){

    if (start>=end){
        return;
    }
    int pivet = arr[end], SepPonter = start;
    for(int i = start; i < end; i++){
        if (arr[i] < pivet){
            swap(arr,i, SepPonter);
            SepPonter++;
        }
    }
    swap(arr, SepPonter, end);
    quicksort(arr, SepPonter-1, start);
    quicksort(arr, end, SepPonter+1);
}

int main(){
    int arr[]={3,5,6,3,6,7};//correct ans 8
    int lenth  =sizeof(arr) / sizeof (arr[0]);
    int unic;

    if (lenth < 2){
        unic = lenth;
    }
    else {
        quicksort(arr, lenth - 1);
        unic = 1;
        for (int i = 0; i < lenth-1; i++) {
            if(arr[i] != arr[i+1]){
                unic++;
            }
        }
    }
    cout<<unic<<endl;
    cout<<unic*(unic-1)<<endl;

}