#include <iostream>
#include<string>


typedef unsigned long long  ul;
int main() {
    std::string in;
    std::getline(std::cin, in);
    ul n = in.length();
    ul len = 0;
    bool word = false;
    //triling index
    ul k = -1, j, i = 0;

    //debug variable
    ul max_idx = -1;

    //longest word
    for (; i < n; ++i) {
        if (!word && in[i] >= 'a') {
            k = i;
            word = true;
        }
        else if (word && in[i] < 'a') {
            word = false;
            if (len < i - k) {
                len = i - k;
                max_idx = k;
            }
        }
    }
    if (word) {
        word = false;
        if (len < n - k) {
            len = n - k;
            max_idx = k;
        }

        std::cout << len << '\n' << max_idx << std::endl;

        return 0;
    }
    len *= 3;


    char* out = new char[len + 1]; // output line buffer
    out[len + 1] = '\n';

    ul idx = 0; //buf top writen idx
    k = 0; //line start idx
    j = 0; //word end idx
    bool comma;
    while (i < n) {
        buf[idx]
    }
}

//once upon a time, in a land far far away lived a princess, whose beauty was yet unmatched
/*
once upon a time, in a land
far far away lived a
princess, whose beauty was
yet unmatched
*/
//a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,yandex
/*
a, b, c, d, e, f,
g, h, i, j, k, l,
m, n, o, p, yandex
*/