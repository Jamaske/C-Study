#include <iostream>
using namespace std;
#include <string>
#include <fstream>

const string filenameIn = "C:\\Users\\Egor\\C++\\LongStringLikeInt\\inp1.txt";
const string filenameOut = "C:\\Users\\Egor\\C++\\LongStringLikeInt\\out.txt";



int main() {
    ofstream out;          // поток для записи
    out.open(filenameOut);//нужно
    ifstream file(filenameIn);
    string a, b, result;




    char Minus='-';
    getline(file, a);
    getline(file, b);
    bool SwapChecking=false;

    int LengthA = a.length(), LenghtB = b.length();

    if (LenghtB > LengthA) {

        result = b;
        int Difference = LenghtB - LengthA;
        for (int i=0; i < Difference; i++) {
            a = '0' + a;
        };

    } else if (LenghtB < LengthA) {
        result = a;
        int Difference = LengthA - LenghtB;
        for (int i(0); i < Difference; i++)
        {
            b = '0' + b;
        };
    } else { result = a; };




    int ResultLength = result.length();
    bool bFlag = false;
    for (int i = ResultLength; i >= 0; i--) {
        result[i] = a[i] + b[i] - 48;
        if (bFlag) { result[i]++; };
        if (result[i] >= 58) {
            result[i] -= 10;
            result[i - 1] = result[i - 1] + 1;
            bFlag = true;
        } else { bFlag = false; }

    }


    ofstream l;          // поток для записи
    l.open(filenameOut, ios::app); // окрытие файла для записи
    if (l.is_open()) {
        l << a<< "+"<< b << "=" << result<<endl;
    }
    file.close();


    cout << a<< "+"<< b << "=" << result<<endl;

    if (a<b) {
        swap(a, b);
        SwapChecking=true;
    }

     ResultLength = result.length();
     bFlag = false;
    for (int i = ResultLength - 1; i >= 0; i--) {
        result[i] = a[i] - b[i];
        if (bFlag) { result[i]--; };
        if (result[i] < 0) {
            result[i] += 58;

            if(result[i-1]==48) result[i-1]+=9;

            result[i - 1] = result[i - 1] - 1;
            bFlag = true;
        }
            else {
            bFlag = false;
            result[i]+=48;
            }

    }
    string NewResult="";
    if (SwapChecking) {
        for (int i = 0; i < result.length() ; i++) {
            if(result[i]!=48){
                for (int j = i; j <  result.length()-i+1; ++j) {

                    NewResult+=result[j];
                }
            }
        }
        cout << b<< "-"<< a << "=" << Minus <<NewResult<<endl;
    }
    else cout << a<< "-"<< b << "=" << result<<endl;

   ofstream in;          // поток для записи
    in.open(filenameOut, ios::app); // окрытие файла для записи
    if (in.is_open()) {
        if (SwapChecking) {in << b<< "-"<< a << "=" << Minus <<NewResult<<endl;}
        else in << a<< "-"<< b << "=" << result<<endl;
    }
file.close();
}





/*
#include <iostream>
using namespace std;
#include <string>


string BigSum(string, string);
string BigSub(string, string);

int main() {
    string a, b;

    getline(cin, a);
    getline(cin, b);

    string sum = BigSum(a, b), sub = BigSub(a, b);
    cout << sub << endl;
}


string BigSum(string x, string y) {
    //приводим длины
    x = x.insert(0, string(max(int(y.length() - x.length()), 0), '0'));
    y = y.insert(0, string(x.length() - y.length(), '0'));
    //суммируем
    for(int i = x.length() - 1; i; i--) {
        if ((x[i] += y[i] - '0') > '9') {x[i] -= 10; x[i - 1] +=1;}
    }
    //если нужно дописываем единицу в новом старшем разряде
    if ((x[0] += y[0] - '0') > '9') {x[0] -= 10; x.insert(0,"1");}
    return x;
}


string BigSub(string x, string y) {
    //приводим длины добавлением не значащих нулей перед коротким числом
    x = x.insert(0, string(max(int(y.length() - x.length()), 0), '0'));
    y = y.insert(0, string(x.length() - y.length(), '0'));
    //лекссикографически сравниваем строки одинаковой длинны
    // что-бы вычитать из большего меньшее, переставляем если нужно
    bool neg = false;
    if (y > x) {swap(x,y); neg = true;}

    for (int i = x.length()-1; i; i--) {//вычитаем
        if((x[i] += -y[i] + '0') < '0') {
            x[i] += 10;
            x[i - 1] -=1;
        }
    }
    x[0] += -y[0] + '0';
    //находим сколько (если есть) мнимых нулей в получившемся числе
    //и обрезаем их
    int i = 0;
    while((x[i] == '0') && (++i < x.length() - 1));
    x = x.substr(i, x.length() - i + 1);
    //добавляем в начало "-" если изначально вычитали из меньшего большее
    if (neg) x = x.insert(0, "-");

    return x;
}
*/

