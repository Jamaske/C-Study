#include <iostream>
#include <vector>
#include <unordered_map>
int main() {
    int list[5] = { 5,3,7,12,2 };
    int len = 10;
    std::vector<int> a(len, 0);
    std::unordered_map<int, std::vector<int>> b;
    for (int i = 0; i < sizeof(list) / sizeof(list[0]); ++i) {
        b[list[i]] = a;
    }
    a[1] = 3;
    for (int i = 0; i < sizeof(list) / sizeof(list[0]); ++i) {
        for (int j = 0; j < len; ++j) {
            std::cout << b[list[i]][j] << std::endl;
        }
    }

}