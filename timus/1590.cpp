#include <iostream>
using namespace std;

void prefix(char *str, int *pi, int lenth) {
    pi[0] = 0;
    int i = 0, j = 0;
    while (++i < lenth) {
        while (str[i] != str[j] && j-->0) j = pi[j];
        pi[i] = ++j;
    }
}

int main() {
    char s[]="aaab";
    int Len = sizeof(s)-1;
    int *pi= new int[Len];
    int Max = 0, Sum = 0;
    for (int start = Len - 1; start >= 0; start--, Max = 0) {
        prefix(s + start, pi + start, Len - start);
        for (int i = start; i < Len; Max = max(Max, pi[i++]));
        Sum += (Len - start) - Max;
    }
    cout << Sum;
}