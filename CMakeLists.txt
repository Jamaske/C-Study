cmake_minimum_required(VERSION 3.23)
project(C++)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -funroll-all-loops")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,16777216")

add_executable(C++ dev/Truth_table_solver.cpp)
