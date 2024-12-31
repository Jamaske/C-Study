/*
there are different types of integer devision.
1) trancate (C/C++ java)
2) floor (Python)
3) ceil
4) rounded
5) Euclidean 

*/

#include <tuple>

auto tranc_div(int a, int b){
    return std::tuple(a/b, a%b);
}

auto floor_div(int a, int b){
    int q = a/b, r = a%b;
    if(b > 0){
        if(a >= 0){
            return std::tuple(q,r)
        }
        else{
            return std::tuple(q - 1, r + b)
        }
    }
    else{
        if(a >= 0){
            return std::tuple(q - 1, r + b)
        }
        else{
            return std::tuple(q, r)
        }
    }

}