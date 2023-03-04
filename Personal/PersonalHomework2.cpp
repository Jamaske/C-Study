#include <iostream>
#include <set>


using namespace std;



int BobleCounter(int arr[],int size){//считает количество инверсий в множестве O(n^2)
    int i, j, firstel;               //бабл сорт всегда делает n(n-1)/2 сравнений, но
    int SwapCounter = 0;             //меняет элементы местами, только, когда они идут не в правильном порядке
    for(i = 0; i < size-1; i++){     //поэтому каждая перестановка уменьшает число инверсий на 1
        firstel = arr[i];            //после сортировки число инверсий равно нулю => число перестановок=число инверсий
        for(j = i+1; j < size; j++){
            if(firstel > arr[j]){
                SwapCounter++;
            }
        }
    }
    return SwapCounter;
}


int main(){
    const int Arrsize = 10;
    int i, j, save, BestBuble, CurBuble, ChengeIndex, ChengeValue;
    int arr[Arrsize] = {12,24,4,26,3,1,9,3,15,16};

    for (i = 0; i < Arrsize; i++){
        cout<< arr[i]<<' ';
    }
    BestBuble = BobleCounter(arr, Arrsize);
    cout<<endl<<"initialy "<< BestBuble <<" replacments neded"<<endl;


    set <int> dict;
    for (i = 0; i < Arrsize; i++){//набор всех уникальных чисел множества
        dict.insert(arr[i]);
    }
    set <int> ::iterator iter;


    for (i = 0; i < Arrsize; i++){//i - индекс изменяемого числа списка
        iter = dict.begin();
        save = arr[i];
        for (;iter != dict.end(); iter++){//перебор всех уникальных числел массива
            arr[i] = *iter;
            CurBuble =  BobleCounter(arr, Arrsize); //сколько перестановок на изменённом массиве сделает BubleSort
            if (CurBuble < BestBuble){
                BestBuble = CurBuble;//Если перестановок меньше, чем в прошлые разы, то записываем изменнеие (индекс и вставленное значение)
                ChengeIndex = i;
                ChengeValue = *iter;
            }
        }

        arr[i] = save;
    }

    arr[ChengeIndex] = ChengeValue;//востанавливаем лучшую найденую последовательность
    for (i = 0; i < Arrsize; i++){
        cout<< arr[i]<<' ';
    }
    cout<<endl<<"after "<< BestBuble<<" replacments"<<endl;


}