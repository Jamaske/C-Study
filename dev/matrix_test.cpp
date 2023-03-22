//#include "Matrix.h"
#include <iostream>

typedef unsigned short us;
typedef unsigned int ui;
template<typename T>
class Matrix{
    const us height, width;
    T *arr;
public:

    Matrix(us height,us width) : height(height), width(width) {
        Matrix::arr = new T[height * width];
    }

    Matrix(Matrix& reference){
        Matrix::width = reference.width;
        Matrix::height = reference.height;
        Matrix::arr = reference.arr;
    }
    //typedef Matrix<T, height, width> equivalent;

    T& operator [](ui idx){

    }

    void read_concole(){//переписать на принимание любого потока для чтения из файла
        for(us i = 0; i < height; i++){
            for(us j = 0; j < width; j++){
                std::cin >> arr[i][j];
            }
        }
    }

    void print_console(){
        for(us i = 0; i < height; i++){
            for(us j = 0; j < width; j++){
                std::cout << arr[i][j] << ' ';
            }
            std::cout << "\n";
        }
    }

    T* operator[](us i){
        return &(arr + i*width);
    }

/*

    Matrix<T> operator + (equivalent other){
        equivalent ret;
        for(us i = 0; i < height; i++){
            for(us j = 0; j < width; j++){
                ret[i][j] = arr[i][j] + other.arr[i][j];
            }
        }
    }

    template<const us other_width>
    Matrix<T, hight, other_width> operator * (Matrix<T, width, other_width> other){//учитываем корректность размеров
        equivalent ret;
        T acc;
        for(us i = 0; i < height; i++){
            for(us j = 0; j < other_width; j++){

                acc = 0;
                for(us k = 0; k < width; k++){
                    acc += arr[i][k] * other.arr[k][j];
                }
                ret[i][j] = acc;
            }
        }
    }
*/


};

int main(){
    us h, w;
    //h = 2; w = 2;
    std::cin >> h >> w;
    int c = 0;
    Matrix<int> a(2,2);
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            a[i]
        }
    }
    c++;


}