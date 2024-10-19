#include <iostream>
#include <immintrin.h>
int main() {
    for (size_t i = 0; i < 1024; ++i) {
        std::cout << i + 1 << ' ' << (2ULL << _bit_scan_reverse(i)) << '\n';
    }

    return 0;
}