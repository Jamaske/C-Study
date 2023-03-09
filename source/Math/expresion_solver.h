#pragma once
#include <string>

struct solve{
    std::string raw_expression;
    std::string pol_notation;

    bool vars[26] = {};




    bool getvar(char name);
    void preprocess();
    void convert_to_polish();
    bool calculate_polish();
    bool calculate_raw();

};