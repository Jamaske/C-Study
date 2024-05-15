#include <iostream>
#include <cstdint>
// -O0 -std=c++23
int f(int arg) {
    char buf[16];
    buf[40] -= 0x31;// магические 
    buf[41] -= 0x1;// строки
    int a = 5 + arg;
    return a;
}

int main() {
    printf("main entrence\n");
    char somechar = 'C';
    int ret = 0x21746572;
    ret = f(5);
    printf("call ret %d\n", ret);
    return 0;
}