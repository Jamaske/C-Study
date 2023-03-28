#include <iostream>
#include <iomanip>







int main(){
    quadr a, b;
    a = 0.1;
    std::cout << std::setprecision(100) << a.high << '\n';
    for(int i = 0; i < 50; i++){
        a.inc(a+0.1);
    }
    std::cout << a.high << '\n' << a.low << '\n' ;

}

/*

int main(){
    int a = 14, b = -7;
    int k, k2, dif, dif2, shift;
    std::cout <<a - (a/b)*b
    << '\n';
    for(a = -15; a < 15; a ++){
        if(!a){std::cout << '\n'; continue;}

        k = a/b; dif = a - b * k;


        //shift = (a > 0? abs(b):-abs(b)) /2;

        k2 = (a / b);
        shift = ( (a-b*k2) << 1) / b;
        k2 = k2 + shift;
        dif2 = a - b * k2;

        std::cout
        << "a: " << a << '\t'
        << "k:" << k << '\t'
        << "dif:" << dif << '\t'
        << '\t'
        << "sh:" << shift << '\t'
        << "k2:" << k2 << '\t'
        << "dif2:" << dif2 << '\t'
        << std::endl;
    }

}*/
