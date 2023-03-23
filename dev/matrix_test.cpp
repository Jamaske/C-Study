//#include "Matrix.h"
#include <iostream>

typedef unsigned short us;
typedef unsigned int ui;
template<typename T>
class Matrix{
    const us height, width;
    const ui size;
    T *arr;
public:

    Matrix(us height,us width):
    height(height), width(width), size(height * width) {
        Matrix::arr = new T[size]{};
    }

    ~Matrix(){delete[] arr;}

    Matrix(Matrix& source):
    height(source.width), width(source.height), size(source.width * source.height){
        Matrix::arr = new T[size];
        memcpy(arr,source.arr, size * sizeof(T));
    }

    Matrix& operator = (const Matrix& scource){
        if(size != scource.size && width != scource.width){
            std::cout << "assigment to different sized matrices is invalid operation\n";
            return nullptr;
        }
        if(this != &scource){ memcpy(arr, scource.arr, height * width * sizeof(T));}
    return *this;//для всяких выражений типа a = 3*(b = c)++; и последовательного присваивания
    }

    void read_concole(){//переписать на принимание любого потока для чтения из файла
        for(ui i = 0; i < size; i++){
            std::cin >> arr[i];
        }
    }
    void print_console(){
        T* end = arr + size;
        for(T* row = arr; row < end; row += width){
            for(us j = 0; j < width; j++){
                std::cout << row[j] << '\t';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    T* operator[](us i){
        return (arr + width * i);
    }


    const Matrix<T>& operator + (const Matrix& right){
        if(size != right.size && width != right.width){
            std::cout << "addition of different sized matrices is invalid operation\n";
            return nullptr;
        }
        Matrix ret;
        for(ui i = 0; i < size; i++){
            ret[i] = arr[i] + right.arr[i];
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
    Matrix<int> a(h,w);

    a.print_console();




}