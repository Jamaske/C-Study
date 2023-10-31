#pragma once

#include <cstdint>
#include <cstring>
#include <random>
#include <iostream>
#include <iomanip>
#include "array_wrapper.h"



template<typename T, std::uint32_t algorithms_count, std::uint32_t bathes, std::uint32_t data_size>
struct test_data{
public:
    T madness[bathes][algorithms_count + 1][data_size];
    //array_wrapper<T> *wrapped_data = new  array_wrapper<T>[bathes][algorithms_count];

    test_data(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> rnd(1, 100);
        for(std::uint32_t i = 0; i < bathes; ++i){

            for(std::uint32_t j = 0; j < data_size; ++j){
                madness[i][algorithms_count][j] = rnd(gen);
            }//генерируем случайную последовательность первой пачки для первого алгоритма
            //wrapped_data[i][0] = wrapped_data(madness[i][0][0], data_size);

            for(std::uint32_t j = 0; j < algorithms_count; ++j){
                std::memcpy(&madness[i][j][0], &madness[i][algorithms_count][0], sizeof(T) * data_size);
                //wrapped_data[i][j] = wrapped_data(madness[i][j][0], data_size);
            }//копируем сгенерированное остальным алгоритмам
        }
    }

    void print_alg_domain(){
        std::cout << "{([" << madness[0][0][0];
        for (std::uint32_t k = 1; k < data_size; ++k) {std::cout << ", " << madness[0][0][k];}
        std::cout << ']';
        for (std::uint32_t j = 1; j < algorithms_count; ++j) {
            std::cout << ",\n  [" << madness[0][j][0];
            for (std::uint32_t k = 1; k < data_size; ++k) {std::cout << ", " << madness[0][j][k];}
            std::cout << ']';
        }
        std::cout << ")";
        for(std::uint32_t i = 1; i < bathes; ++i) {
            std::cout << ";\n\n ([" << madness[i][0][0];
            for (std::uint32_t k = 1; k < data_size; ++k) {std::cout << ", " << madness[i][0][k];}
            std::cout << ']';
            for (std::uint32_t j = 1; j < algorithms_count; ++j) {
                std::cout << ",\n  [" << madness[i][j][0];
                for (std::uint32_t k = 1; k < data_size; ++k) {std::cout << ", " << madness[i][j][k];}
                std::cout << ']';
            }
            std::cout << ")";
        }
        std::cout << "}\n";
    }

    void print_data_source(){
        std::cout << "i="<< std::setw(4) << std::left << 0 << " [" << std::setw(3) << madness[0][algorithms_count][0];
        for (std::uint32_t k = 1; k < data_size; ++k) {std::cout << ", " << madness[0][algorithms_count][k];}
        std::cout << ']';
        for(std::uint32_t i = 1; i < bathes; ++i){
            std::cout << ",\ni="<< std::setw(4) << std::left << i << " [" << std::setw(3) << madness[i][algorithms_count][0];
            for (std::uint32_t k = 1; k < data_size; ++k) {std::cout << ", " << madness[i][algorithms_count][k];}
            std::cout << ']';
        }
    }


};