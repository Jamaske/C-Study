#include <iostream>

void inc(){
    static std::string n;
    n = n + "a";
    std::cout << n<< std::endl;
}

int main(){
    static std::string n = "";
    inc();
    inc();
    inc();
}