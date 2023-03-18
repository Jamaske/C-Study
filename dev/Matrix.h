#pragma once
#include <iostream>

typedef unsigned short us;
template<typename T, const us hight, const us width>
class Matrix{
    T arr[hight][width];

public:
    typedef Matrix<T, hight, width> equivalent;

    void read_concole(){//переписать на принимание любого потока для чтения из файла
        for(us i = 0; i < hight; i++){
            for(us j = 0; j < width; j++){
                std::cin >> arr[i][j];
            }
        }
    }

    void print_console(){
        for(us i = 0; i < hight; i++){
            for(us j = 0; j < width; j++){
                std::cout << arr[i][j] << ' ';
            }
            std::cout << "\n";
        }
    }

    equivalent operator + (equivalent other){
        equivalent ret;
        for(us i = 0; i < hight; i++){
            for(us j = 0; j < width; j++){
                ret[i][j] = arr[i][j] + other.arr[i][j];
            }
        }
    }

    template<const us other_width>
    Matrix<T, hight, other_width> operator * (Matrix<T, width, other_width> other){//учитываем корректность размеров
        equivalent ret;
        T acc;
        for(us i = 0; i < hight; i++){
            for(us j = 0; j < other_width; j++){

                acc = 0;
                for(us k = 0; k < width; k++){
                    acc += arr[i][k] * other.arr[k][j];
                }
                ret[i][j] = acc;
            }
        }
    }
};
