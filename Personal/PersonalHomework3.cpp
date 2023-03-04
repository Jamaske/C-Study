#include <iostream>

using namespace std;

int* binomialCoefitians(int n) {
    int* const arr = new int[n]{1};

    for (int k = 1; k <= n; k++){
        arr[k] = (arr[k-1] * (n - k + 1)) / k;//умножаем прошлый ою расстановку на соотношение текущего биномиального коэффициента
        // C[k,n] = C[k-1,n] * (C[k,n] / C[k-1,n]) где C[k,n] / C[k-1,n] сокращается до ((k-1)! * (n-k+1)!)/(k! * (n-k)!) = (n-k+1)/k
    }
    return arr;
}


int main(){
    int n;
    cin >> n;
    const int* const binomial = binomialCoefitians(n);

    for (int i = 0; i < n; i++){
        cout<< binomial[i] << "*" << "a^" << i << "*b^" << n-i << " + ";
    }
    cout<< binomial[n] << "*" << "a^" << n << "*b^" << 0 << endl;

    delete[] binomial;
}