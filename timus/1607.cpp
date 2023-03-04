#include <iostream>
using namespace std;

int main() {
    int prise1, prise2, step1, step2, turns;
    cin >> prise1 >> step1 >> prise2 >> step2;

    while(prise1<=prise2){
        prise1 += step1;
        if (prise1>prise2){
            prise1 = prise2;
        }
        prise2 -= step2;

    }
    cout<<prise1;
}