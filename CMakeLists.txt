cmake_minimum_required(VERSION 3.23)
project(C++)

set(CMAKE_CXX_STANDARD 20)

add_executable(C++ dev/test_main.cpp dev/expresion_solver.h dev/expresion_solver.cpp)
