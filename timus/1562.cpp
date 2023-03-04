#include<iostream>
#include <iomanip>
using namespace std;

int main(){
    double a, b;
    int n;
    cin >> a >> b >> n;
    double d, d2, A, B, C, k;
    k = (3.14159265358979323846 * a * a)/(6 * b * b);
    d = b/n;

    cout << fixed << setprecision(6);
    double Vcur, Vprev = 0;
    for(double  x = d; x <= b; x += d){
        Vcur = k*(3*b*x*x - 2 * x * x * x);
        cout << Vcur - Vprev<< endl;
        Vprev = Vcur;
    }
}
/*
k = 3.14159265358979323846*a*a/(b*n);
d = b/n;
d2 = d*d;
C = k;
B = (n-1)*(k = k * d);
A = (3*n - 2) * (k * d / 6);
for(double x = 0, x2 = 0; x < b; x += d){
    x2 += (x*d)*2 + d2;
    cout << A*x2 + B*x + C << endl;
}
 */