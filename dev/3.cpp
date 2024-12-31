#include <iostream>

void Div(int a, int b) {
    std::cout << "a, b = " << a << ", " << b << "  \ta/b = " << a / b << "  \ta%b = " << a % b << '\n';
}


int main() {
    Div(3, 2);
    Div(-3, 2);
    std::cout << "b newgative \n";
    Div(3, -2);
    Div(-3, -2);
}