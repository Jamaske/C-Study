//#include "Matrix.h"
#include <iostream>

typedef unsigned short us;
typedef unsigned int ui;

template<typename T>
class Matrix {
    const us height, width;
    const ui size;
    T *arr;
public:

    Matrix(us height, us width) :
            height(height), width(width), size(height * width) {
        Matrix::arr = new T[size]{};
    }

    ~Matrix() { delete[] arr; }

    Matrix(Matrix &source) :
            height(source.height), width(source.width), size(source.height * source.width) {
        Matrix::arr = new T[size];
        memcpy(arr, source.arr, size * sizeof(T));
    }

    Matrix &operator=(const Matrix &scource) {
        if (size != scource.size && width != scource.width) {
            std::cout << "assigment to different sized matrices is invalid operation\n";
        }
        if (this != &scource) { memcpy(arr, scource.arr, size * sizeof(T)); }
        return *this;//для всяких выражений типа a = 3*(b = c)++; и последовательного присваивания
    }

    void read_concole() {//переписать на принимание любого потока для чтения из файла
        for (ui i = 0; i < size; i++) {
            std::cin >> arr[i];
        }
    }

    void print_console() {
        T *end = arr + size;
        for (T *row = arr; row < end; row += width) {
            for (us j = 0; j < width; j++) {
                std::cout << row[j] << '\t';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    T *operator[](us i) {
        return (arr + width * i);
    }

    const Matrix<T> operator+(const Matrix &right) {
        if (size != right.size && width != right.width) {
            std::cout << "addition of different sized matrices is invalid operation\n";
            return nullptr;
        }
        Matrix ret;
        for (ui i = 0; i < size; i++) {
            ret[i] = arr[i] + right.arr[i];
        }
        return ret;//возврат через конструктор копирования в безымянную переменную во внешней области видимости
    }

    const Matrix<T> operator-(const Matrix &right) {
        if (size != right.size && width != right.width) {
            std::cout << "addition of different sized matrices is invalid operation\n";
            return nullptr;
        }
        Matrix ret;
        for (ui i = 0; i < size; i++) {
            ret[i] = arr[i] - right.arr[i];
        }
        return ret;//возврат через конструктор копирования в безымянную переменную во внешней области видимости
    }

    const Matrix<T> operator*(const Matrix<T> right) {//учитываем корректность размеров
        if (width != right.height) {
            std::cout << "multiplication of incompatible sized matrices\n";
        }
        Matrix res(height, right.width);

        T *left_cell, *right_cell, *res_row, *res_row_next, *res_cell;//указательная арифметика для итерации по матрицам
        T *left_end = arr + size, *right_end = right.arr + right.size;//адреса - ограничители
        T left_value;

        res_row = res.arr;
        for (left_cell = arr; left_cell < left_end; res_row = res_row_next) {
            res_row_next = res_row + res.width;
            for (right_cell = right.arr; right_cell < right_end; ++left_cell) {
                left_value = *left_cell;//кеширование для уменьшения количества разыменований
                for (res_cell = res_row; res_cell < res_row_next; ++right_cell) {
                    *res_cell++ += left_value * *right_cell;//грязь
                }
            }
        }
        return res;
    }

    const Matrix<T> operator!() {//транспонирование
        Matrix trans(width, height);
        T const *end = arr + size, *row = arr + width;
        for (T *i = arr, *j = trans.arr; i < end || (i = ++i - size) < row; i += width, ++j) {
            *j = *i;
        }
        return trans;
    }

    template<typename U>
    friend void Gaus(Matrix<U> &solve, Matrix<U> &add);
};


template<typename U = int>
void Gaus(Matrix<U> &solve, Matrix<U> &add) {
    if (solve.height != add.height) std::cout << "Gaus method need matrices with same height\n";

    U *row_buffer = new U[std::max(solve.width, add.width)];//для перестановки строк местами
    us width = solve.width, height = solve.height;

    U smallest, prev_smallest, cur, k;
    us prev_smallest_row, smallest_row, row, column;
    us row_completion = 0, column_completion;
    bool flg;

    for (column_completion = 0; column_completion < width; column_completion++) {//Перебираем столбцы и приводим к ступенчатому виду. Далее текущий приводимый столбец называется рабочим.
        //Также помимо переменной указывающей количество законченных столбцов есть переменная для строк, которые нельзя вычитать из тех, что ниже, чтобы не попортить готовые нули.
        //Область правее column_completion и ниже row_completion, на которой матрица ещё не приведена, далее называется рабочей областью
        std::cout << "====column: " << column_completion <<std::endl;


        for(row = row_completion; row < height && !solve[row][column_completion]; ++row);//ищем первое не нулевое значение в рабочем столбце
        if (row >= height) continue;//если не нашли - скипаем столбец

        smallest = solve[ (smallest_row = row) ][column_completion];
        while(++row < height){//ищем строчку с наименьшим не нулевым значением ниже готовых строк
            cur = solve[row][column_completion];
            if(cur && abs(cur) < abs(smallest)) {
                smallest_row = row;
                smallest = cur;
            }
        }

        do {//вычитаем строки между друг другом как в алгоритме Евклида в рабочей области
            prev_smallest_row = smallest_row;
            prev_smallest = smallest;
            std::cout << "smallest: " << prev_smallest << '\n';
            flg = false;//флаг говорящий о том, что в рабочей области остаются не нулевые значения

            for (row = row_completion; row < height; ++row) {//вычетаем из всех недоделанных строк данную с нужными коэффициентами
                if (row == prev_smallest_row) continue;//вычитать саму из себя нельзяб
                k = (solve[row][column_completion] + (prev_smallest >> 1)) / prev_smallest; //считаем сколько раз из текущей строки нужно вычесть наименьшую
                if (k) {
                    std::cout << "k = " << k << ":\t";
                    for (column = column_completion; column < width; ++column) {
                        solve[row][column] -= k * solve[prev_smallest_row][column];
                        std::cout <<solve[row][column] << '\t';
                    }
                    for (column = 0; column < add.width; ++column) {
                        add[row][column] -= k * add[prev_smallest_row][column];
                    }
                    std::cout << '\n';
                }
                cur = solve[row][column_completion];
                if (cur) {//проверяем остаётся ли в рабочем столбце не нулевое число
                    flg = true;
                    if (abs(cur) < abs(smallest))
                        smallest = solve[(smallest_row = row)][column_completion];
                }
            }

        } while (flg);
        std::cout << "----upper rows---\n";
        for(row = 0; row < row_completion; ++row){

            k = solve[row][column_completion] / smallest;
            if (k) {
                std::cout << "k = " << k << ":\t";
                for (column = column_completion; column < width; ++column) {
                    solve[row][column] -= k * solve[smallest_row][column];
                    std::cout <<solve[row][column] << '\t';
                }
                for (column = 0; column < add.width; ++column) {
                    add[row][column] -= k * add[smallest_row][column];
                }
            }
            std::cout << '\n';


        }

        if (smallest_row != row_completion) {//если строка с последним числом не наверху рабочей области - свапаем её туда
            //свапоем solve
            ui len = (width - column_completion) * sizeof(U);
            U *top_row = solve[row_completion] + column_completion;
            U *nonzero_row = solve[smallest_row] + column_completion;
            memcpy(row_buffer, top_row, len);
            memcpy(top_row, nonzero_row, len);
            memcpy(nonzero_row, row_buffer, len);
            //и add
            len = add.width * sizeof(U);
            top_row = add[row_completion];
            nonzero_row = add[smallest_row];
            memcpy(row_buffer, top_row, len);
            memcpy(top_row, nonzero_row, len);
            memcpy(nonzero_row, row_buffer, len);
        }
        ++row_completion;
    }

}

int main() {

    us h, w;
    //h = 2; w = 2;
    //std::cin >> h >> w;
    int count = 0;
    Matrix<int> a(4, 4);
    Matrix<int> b(4, 4);

    srand( 15);
    for (int i = 0; i < 4; ++i) {
           for (int j = 0; j < 4; ++j) {
               a[i][j] = rand()%10;
           }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            b[i][j] = rand()%10;
        }
    }
    a.print_console();
    //b.print_console();
    Gaus(a, b);
    std::cout << "======================" <<std::endl;
    a.print_console();
    b.print_console();


}