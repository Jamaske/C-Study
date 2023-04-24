#include<iostream>
#include <string>
#include <fstream>


using namespace std;
const string filenameIn = "C:\\Users\\Egor\\C++\\Individual6\\inp1.txt";


int main() {
    string s; //переменная для записи строки из файла
    ifstream fin;//(filenameIn);
    fin.open(filenameIn);
    int Quantity, Size;
    fin >> Quantity >> Size;
    int Min, l;
    int * MinOfMatrix=new int[Quantity];
    bool PreviousNotTrigle=false;
    int Real=0;
    int TringleCounter=0;
    int** temp;

    int*** Arr=new int**[Quantity];
    for (int i = 0; Real < Quantity; ++i) {
        if(PreviousNotTrigle){
            PreviousNotTrigle=false;
            i--;
            Min = 10000000;
            for (int j = 0; j < Size; ++j) {
                for (int k = 0; k < Size; ++k) {
                    fin >> l;
                    Arr[i][j][k] = l;
                    if (j > k ){
                        if (Arr[i][j][k] != Arr[i][k][j]) {
                            PreviousNotTrigle = true;
                        }
                    }
                    if (l < Min) Min = l;
                }
            }
        }else {
            PreviousNotTrigle=false;
            Min = 10000000;
            Arr[i] = new int *[Size];
            for (int j = 0; j < Size; ++j) {
                Arr[i][j] = new int[Size];
                for (int k = 0; k < Size; ++k) {
                    fin >> l;
                    Arr[i][j][k] = l;
                    if (j > k ){
                        if (Arr[i][j][k] != Arr[i][k][j]) {
                            PreviousNotTrigle = true;
                        }
                    }
                    if (l < Min) Min = l;
                }
            }

        }
        MinOfMatrix[i] = Min;
        Real++;
        TringleCounter=i+1;
    }
    if(PreviousNotTrigle) TringleCounter--;

    for (int i = 0; i < TringleCounter; i++) {
        for (int j = 0; j < TringleCounter-1; j++) {
            if (MinOfMatrix[j] > MinOfMatrix[j + 1]) {
                int b = MinOfMatrix[j];
                MinOfMatrix[j] = MinOfMatrix[j + 1];
                MinOfMatrix[j + 1] = b;

                temp = Arr[j];
                Arr[j]=Arr[j+1];
                Arr[j + 1] = temp;
            }
        }
    }


    for (int i = 0; i < TringleCounter; ++i) {
        cout << MinOfMatrix[i] << endl;
        for (int j = 0; j < Size; ++j) {

            for (int k = 0; k < Size; ++k) {
                cout << Arr[i][j][k] << " " ;

            }
            cout << endl;
        }
        cout << endl;


    } //cout Matrix





}