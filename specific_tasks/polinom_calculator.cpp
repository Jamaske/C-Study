#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;
const string InputPath = "C:\\Users\\User\\data\\my_scripts\\C++\\inp1.txt";
const string OutputPath = "C:\\Users\\User\\data\\my_scripts\\C++\\out.txt";

void Swap2(int i, int j,int *arr, int* arr2){
    int tmp = arr[j];
    arr[j] = arr[i];
    arr[i] = tmp;

    tmp = arr2[j];
    arr2[j] = arr2[i];
    arr2[i] = tmp;
}

void IDK_sort(int* arr, int start, int end, int* arr2){
    //start - индекс первого элемента
    //end - индекс следующий за последним (не включительно)
    if(end - start <= 2){
        if (arr[start + 1] > arr[start]) return;
        Swap2(start, start + 1, arr, arr2);
        return;
    }

    int sep = (start + end) / 2;//начало второй половины
    IDK_sort(arr, start, sep , arr2);
    IDK_sort(arr, sep, end, arr2);

    int* temp = new int[end - start + 1];
    int* temp2 = new int[end - start + 1];
    int i = start, j = sep, k = start;
    while((i < sep) && (j < end)){
        if (arr[i] > arr[j]) {
            temp[k] = arr[i];
            temp2[k++] = arr2[i++];
        }
        else {
            temp[k] = arr[j];
            temp2[k++] = arr2[j++];
        }
    }
    while(i < sep) {
        copy(arr + i ,sep - 1, temp + k);
    }


}

int main(){
    int x;
    string inp;
    ifstream fin;
    fin.open(InputPath);
    if (!fin.is_open()){
        cout << "file can't open file";
        return 1;
    }
    fin >> x;
    getline(fin, inp);
    getline(fin, inp);
    fin.close();
    int Len = 0;
    for (int i = inp.length(); i; i--) if (inp[i]==' ') Len++;
    Len = (Len+1)/2;
    int *weights = new int[Len];
    int *powers = new int[Len];
    int p = -1, q = inp.find(' ', p + 1);
    for (int i = 0; i < Len - 1; i++){

        powers[i] = stoi(inp.substr(p + 1, q - p - 1));
        p = q;
        q = inp.find(' ', p + 1);
        weights[i] = stoi(inp.substr(p + 1, q - p - 1));
        p = q;
        q = inp.find(' ', p + 1);
    }
    powers[Len-1] = stoi(inp.substr(p + 1, q - p - 1));
    weights[Len-1] = stoi(inp.substr(q + 1, inp.length() - q - 1));

    for (int i = 0; i < Len; i++){
        cout << weights[i]<< "x^" <<powers[i] << endl;
    }



}