#include "BitSet.h"
#include <iostream>


int main(){
    int a = 1;
    const int Copy = a;
    int & ra = a;
    const int & cra = a;
    //possible assignments/initializations
    //from int to:
    //int -> int&
    //int -> const int
    //int -> int&
    //int -> const int&

    //from const int to:
    //const int -/>int
    //const int -> const int
    //const int -/>int&
    //const int -> const int&

    //conclusion:
    //changeable types can be converted to constant
    //but constant can't to changeable
    //note: constant flag make

    std::cout << "a:" << a << " ref_a: " << ra << " const_ref_a: " << cra << " const_copy_a: " << Copy << '\n';

    a = 2;
    std::cout << "a:" << a << " ref_a: " << ra << " const_ref_a: " << cra << " const_copy_a: " << Copy << '\n';


    ra = 3;
    std::cout << "a:" << a << " ref_a: " << ra << " const_ref_a: " << cra << " const_copy_a: " << Copy << '\n';


}