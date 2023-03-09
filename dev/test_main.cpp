#include <iostream>
#include "expresion_solver.h"

int main(){
    solve tsk;
    tsk.raw_expression = "NOT((A OR NOT B) AND (A OR B)) OR NOT (A AND NOT B OR TRUE)";
    std::cout << tsk.raw_expression << std::endl;

    tsk.preprocess();
    std::cout << tsk.raw_expression << std::endl;

    std::cout << tsk.calculate_raw() << std::endl;

    tsk.convert_to_polish();
    std::cout << tsk.pol_notation << std::endl;

    std::cout << tsk.calculate_polish() << std::endl;
}

