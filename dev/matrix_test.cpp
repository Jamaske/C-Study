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
    height(source.height), width(source.width), size(source.height * source.width){
        Matrix::arr = new T[size];
        memcpy(arr,source.arr, size * sizeof(T));
    }

    Matrix& operator = (const Matrix& scource){
        if(size != scource.size && width != scource.width){
            std::cout << "assigment to different sized matrices is invalid operation\n";
        }
        if(this != &scource){ memcpy(arr, scource.arr, size * sizeof(T));}
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

    const Matrix<T> operator + (const Matrix& right){
        if(size != right.size && width != right.width){
            std::cout << "addition of different sized matrices is invalid operation\n";
            return nullptr;
        }
        Matrix ret;
        for(ui i = 0; i < size; i++){
            ret[i] = arr[i] + right.arr[i];
        }
        return ret;//возврат через конструктор копирования в безымянную переменную во внешней области видимости
    }

    const Matrix<T> operator - (const Matrix& right){
        if(size != right.size && width != right.width){
            std::cout << "addition of different sized matrices is invalid operation\n";
            return nullptr;
        }
        Matrix ret;
        for(ui i = 0; i < size; i++){
            ret[i] = arr[i] - right.arr[i];
        }
        return ret;//возврат через конструктор копирования в безымянную переменную во внешней области видимости
    }

    const Matrix<T> operator * (const Matrix<T> right){//учитываем корректность размеров
        if(width != right.height){
            std::cout << "multiplication of incompatible sized matrices\n";
        }
        Matrix res(height, right.width);

        T *left_cell, *right_cell, *res_row, *res_row_next, *res_cell;//указательная арифметика для итерации по матрицам
        T *left_end = arr + size, *right_end = right.arr + right.size;//адреса - ограничители
        T left_value;

        res_row = res.arr;
        for(left_cell = arr; left_cell < left_end; res_row = res_row_next){
            res_row_next = res_row + res.width;
            for(right_cell = right.arr; right_cell < right_end; ++left_cell){
                left_value = *left_cell;//кеширование для уменьшения количества разыменований
                for(res_cell = res_row; res_cell < res_row_next; ++right_cell){
                    *res_cell++ += left_value * *right_cell;//грязь
                }
            }
        }
        return res;
    }

    const Matrix<T> operator ! (){//транспонирование
        Matrix trans(width, height);
        T const *end = arr + size, *row = arr + width;
        for(T *i = arr, *j = trans.arr; i < end || (i = ++i - size) < row; i += width, ++j){
            *j = *i;
        }
        return trans;
    }


    friend void Gaus(Matrix<T>& solve, Matrix<T>& add);
};



template <typename T>
void Gaus(Matrix<T>& solve, Matrix<T>& add){
    if(solve.height != add.height) std::cout << "Gaus method need matrices with same height\n";

    T* tmp_solve_row = new T[solve.width];//для перестановки строк местами
    T* tmp_add_row = new T[add.width];
    us width = solve.width, height = solve.height;

    us smallest, next_smallest;
    us row_completion = 0, column_completion;
    for(column_completion = 0; column_completion < width; column_completion++){

        smallest = -1;
        for(us row = row_completion; row < height; ++row){//ищем строчку с наименьшим не нулевым значением ниже готовых строк
            if(solve[row][column_completion]){
                if(smallest < 0 || abs(solve[row][column_completion]) < abs(solve[smallest][column_completion])) smallest = row;
            }
        }
        if(smallest < 0) continue;//в столбце либо только нули, либо нули ниже готовых строк - скипаем


        bool flg;
        do{//вычитаем строки между друг другом
            next_smallest = -1;
            flg = false;
            T k;
            for (us row = row_completion; row < height; ++row) {//вычетаем из всех недоделанных строк данную с нужными коэффициентами
                if (row == smallest) continue;//вычитать саму из себя нельзяб
                k = solve[row][column_completion] / solve[smallest][column_completion]; //считаем сколько раз из текущей строки нужно вычесть наименьшую
                if (k) {
                    for (us column = column_completion; column < width; ++column) {
                        solve[row][column] -= k * solve[smallest][column];
                    }
                    for (us column = 0; column < add.width; ++column) {
                        add[row][column] -= k * add[smallest][column];
                    }
                }
                if(solve[row][column_completion]){
                    flg = true;
                    if(next_smallest < 0 || abs(solve[row][column_completion]) < abs(solve[next_smallest][column_completion])) next_smallest = row;
                }
            }
            smallest = next_smallest;
        }while(flg);

        if(smallest != row_completion){//если строка с последним числом не наверху рабочей области - свапаем её туда
            //свапоем solve
            ui len = (width - column_completion) * sizeof(T);
            T* top_row = solve[row_completion] + column_completion;
            T* nonzero_row = solve[smallest] + column_completion;
            memcpy(tmp_solve_row, top_row, len);
            memcpy(top_row, nonzero_row, len);
            memcpy(nonzero_row, tmp_solve_row, len);
            //и add
            len = add.width * sizeof(T);
            top_row = add[row_completion];
            nonzero_row = add[smallest];
            memcpy(tmp_add_row, top_row, len);
            memcpy(top_row, nonzero_row, len);
            memcpy(nonzero_row, tmp_add_row, len);
        }
        ++row_completion;
    }

}

int main(){
    us h, w;
    //h = 2; w = 2;
    //std::cin >> h >> w;
    int count = 0;
    Matrix<int> a(3,4);



    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 4; ++j){
            a[i][j] = count++;
        }
    }
    a.print_console();
    Matrix b(!a);
    //b.print_console();
    Matrix c(b * a);
    //c.print_console();
    Matrix d(!c);
    //d.print_console();
    Gaus<int>(a, c);





}