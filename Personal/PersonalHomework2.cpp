#include <iostream>
#include <set>


using namespace std;



int BubbleCounter(int arr[],int size){//считает количество инверсий в множестве O(n^2)
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
    int i, j, save, BestBubble, CurBuble, ChangeIndex, ChangeValue;
    int arr[Arrsize] = {12,24,4,26,3,1,9,3,15,16};

    for (i = 0; i < Arrsize; i++){
        cout<< arr[i]<<' ';
    }
    BestBubble = BubbleCounter(arr, Arrsize);
    cout<<endl<<"initially "<< BestBubble <<" replacments needed"<<endl;


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
            CurBuble =  BubbleCounter(arr, Arrsize); //сколько перестановок на изменённом массиве сделает BubbleSort
            if (CurBuble < BestBubble){
                BestBubble = CurBuble;//Если перестановок меньше, чем в прошлые разы, то записываем изменнеие (индекс и вставленное значение)
                ChangeIndex = i;
                ChangeValue = *iter;
            }
        }

        arr[i] = save;
    }

    arr[ChangeIndex] = ChangeValue;//востанавливаем лучшую найденую последовательность
    for (i = 0; i < Arrsize; i++){
        cout<< arr[i]<<' ';
    }
    cout<<endl<<"after "<< BestBubble<<" replacments"<<endl;


}