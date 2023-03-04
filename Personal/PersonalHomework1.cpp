/*
Индивидуальное домашнее задание №1. Циклические алгоритмы
Чернявский Дмитрий Вариант 4
*/

#include <iostream>
#include <cmath>
using namespace std;


int main(){
    bool debug = false;
    unsigned long int enterednum, maxValue, tempValue, SplitPoint;
    cin>>enterednum;
    short int maxCount, len = log10(enterednum)+1, tempCount;
    SplitPoint = 1;
    for (short i = 0; i < len + 1; i++){//перебираем все позиции делим данное число на правую и левую половинки

        unsigned long int right= enterednum % SplitPoint, left = enterednum - right;

        if (debug) cout<<i<<" position"<<endl;

        for (short g = (i==len); g < 10; g++){//перебираем цифры от 0 до 9 и вставляем их между половинками (для самой левой позиции, когда i==len, считаем не с 0, а с 1 )
            tempValue = left * 10 + g * SplitPoint + right;
            unsigned long int n = tempValue;
            tempCount=1;

            for(unsigned long int i=2;i<=n;i++){//находим делитель числа (простой)
                if (n%i==0) {
                    short int curDivPow = 0;
                    do {//делеим чило на его делитель столько раз сколько сможем
                        n = n / i;
                        curDivPow += 1;
                    } while (n % i == 0);
                    //cout<<i<<"^"<<curDivPow<<endl;
                    tempCount *= (curDivPow + 1);//по формуле пересчитываем степени простых множителей числа в колличество делителей n=(a^x1)*(b^x2)*(c^x3)...  deviders=(1+x1)(1+x2)(1+x3)...
                }
            }
            if (debug) cout<<tempValue<<" -> "<<tempCount<<endl;

            if (tempCount > maxCount){//находим из них то, у которых больше всех делителей
                maxCount = tempCount;
                maxValue = tempValue;
            }
        }
        if (debug) cout<<endl;
        SplitPoint *=10;
    }

    unsigned long int n = enterednum;
    tempCount=1;
    for(unsigned long int i=2;i<=n;i++) {//кросота для консоли
        if (n % i == 0) {
            short int curDivPow = 0;
            do {
                n /= i;
                curDivPow += 1;
            } while (n % i == 0);
            //cout<<i<<"^"<<curDivPow<<endl;
            tempCount *= (curDivPow + 1);
        }
    }

    cout<<enterednum<<" =>  "<<tempCount<<endl;
    cout<<maxValue<<" => "<<maxCount<<endl;
}
