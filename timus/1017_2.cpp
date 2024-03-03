#include <iostream>
#include <cmath>
#include <stdint.h>
typedef uint64_t ull;
typedef uint16_t us;


int main(void)
{
    short N;
    std::cin >> N;
    ull* ladders = new ull[N + 1] {0};//eventually will hold number of combination of ladders with idx amount of cubes in it
    ladders[0]=1;

    us zero_buffer_end = ((us)std::sqrt( (N<<3) - 7) - 1)>>1;
    us relevant_idx = 1;
    us h = 1;
    for (; h <= zero_buffer_end; relevant_idx += h++) {
        for (us n = relevant_idx; n-->0;)
            ladders[n + h] += ladders[n];
    }

    for (; h <= N; ++h) // h = height of new ladder in new combinations
        for (us n = N + 1 - h; n-->0;)// n = number of cubes in source combinations // n-->0 - decreasing unsigned n overflow catching solution
            ladders[n + h] += ladders[n];
    // amount combinations of ladders with height (= h) and number of cubes (= n + h) is equal
    // to amount of combinations of stair with height less (< h)  and number of cubes equal to (= n)

    std::cout << ladders[N];
}