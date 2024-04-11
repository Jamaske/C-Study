#include <cstdio>
#include <bit>
#include <cstdint>

#define BINARY_BUFFER_SIZE (size_t)1024 * 1024 * 4
#define BINARY_MIN_BLOCK_SIZE (size_t)8

static_assert(sizeof(void*) <= BINARY_MIN_BLOCK_SIZE && BINARY_MIN_BLOCK_SIZE <= BINARY_BUFFER_SIZE);
static_assert(std::has_single_bit(BINARY_BUFFER_SIZE));
static_assert(std::has_single_bit(BINARY_MIN_BLOCK_SIZE));




static inline uint64_t calcPow(size_t size) noexcept {
    static constexpr int min_pow = 62 - __builtin_clzll(BINARY_MIN_BLOCK_SIZE);
    uint64_t log;
    // inline assembly with bsr instruction (Bit Scan Reverse)
    // find index of most significant (rightest) set (1) bit in an integer
    asm("bsr %1, %0" : "=r"(log) : "r"((size - 1) >> min_pow));
    return log;
}


int main() {

    printf("%d\n", calcPow(5));
    return 0;
}