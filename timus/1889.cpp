#include <iostream>
#include <string>
using namespace std;

int main(){
    int N; cin >> N;
    string curLine, prevLang;
    string *lang = new string[N];
    int* FirstIDXs = new int[N];
    int* LastIDXs = new int[N];
    int LastLang = 0;
    bool No_s_fit = true;

    //создаём список со всеми языками и индексами првого и последнего
    for(int i = 0; i < N; i++){
        cin >> curLine;
        if(curLine == "unknown") continue;
        if(curLine == prevLang) {
            LastIDXs[LastLang - 1] = i;
            continue;
        }

        //когда встретил язык отличный от прошлого проверяем встречали ли мы его ранее
        for(int j = LastLang - 2; j >= 0; j--){
            //если такой язык уже был, значит между предложениями на нём вклинен другой -> Igor debil
            if (lang[j] == curLine){
                cout << "Igor is wrong.";
                goto exit;
            }
        }
        //вышли -> это правда новый язык
        FirstIDXs[LastLang] = i;
        LastIDXs[LastLang] = i;
        lang[LastLang++] = curLine;
        prevLang = curLine;
    }
    FirstIDXs[LastLang] = N;

\

    //для всех делителей N
    if(LastLang == 0){
        cout << LastLang <<' ';
        goto exit;
    }

    int a, b;
    for(int s = N; s >0 ; s--){
        if(N % s) continue;

        //если известно о 0 или 1 языках, то все делители подходят


        //проверяем каждый язык на вхождение в конкретные строки

        //костыль для "первой" итерации
        a = max(0, LastIDXs[0] + 1 -s);
        b = min(FirstIDXs[0], FirstIDXs[1] - s);
        if (a/s + (a%s&&1) > b / s | b < 0) continue;

        for(int i = 1; i < LastLang; i ++){
        a = max(LastIDXs[i - 1] + 1, LastIDXs[i] + 1 - s);
        //cout <<i << ' '<< FirstIDXs[i]<< ' '<< FirstIDXs[i + 1] - s<<endl;
        b = min(FirstIDXs[i], FirstIDXs[i + 1] - s);
        //cout <<a/s+a%s << ' ' <<  b / s<< endl;
        if (a/s + (a%s&&1) > b / s) {
            goto skip;}
        }
        No_s_fit = false;
        cout << N/s <<' ';
        skip:;
    }
    if(No_s_fit){ cout <<"Igor is wrong."<<endl;}

    exit:;
}