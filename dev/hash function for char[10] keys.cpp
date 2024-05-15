#include<cstdio>
#include<cstdint>
/*
    0000FF0000FF00FF
  FF00FF0000FF00FF
FF00FF0000FF0000
*/


// perfect hash function for english lower case 10 latter keys
uint64_t hash(char const* const buf) {
    uint64_t x = (*reinterpret_cast<uint64_t const*>(buf + 0) & 0x0000FF0000FF00FFull) << 5;
    uint64_t y = (*reinterpret_cast<uint64_t const*>(buf + 1) & 0xFF00FF0000FF00FFull);
    uint64_t z = (*reinterpret_cast<uint64_t const*>(buf + 2) & 0xFF00FF0000FF0000ull) >> 5;
    return (0x9BEB7BF7F37BEB7Full + x) + (y + z); // 0x9BEB7BF7F37BEB7Full == -(0x641484080c841481ull) tecnivcaly works without constant whatsoever
}

int main() {
    char buf[11] = "aaaaaaaaaa";

    uint64_t res = hash(buf);
    printf("hash is: %lld\n", res);
    return 0;
}