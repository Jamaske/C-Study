#include <iostream>
#include <fstream>
#include <cstdint>
using namespace std;

// whole lookup table
static const uint32_t anchors[25] = {
    70,
    330,
    1001, 3432,
    2380, 19448,
    4845, 77520, 184756,
    8855, 245157, 1144066,
    14950, 657800, 5311735, 10400600,
    23751, 1560780, 20030010, 67863915,
    35960, 3365856, 64512240, 347373600, 601080390};

// Calculate liniarized index for a 2D quorter-triangle table whare each row has ceil(column/2) enties.
// Allow to not store zeros and only one copy of simetrical values
static inline uint8_t Tri_xy_to_idx(uint32_t x, uint32_t y) {
    return ((x / 2) + 1) * ((x / 2) + (x % 2)) + y;
}


/*
Identities that relate adjasant binomial coefficient.
Takes {base} = C(n + (dn-1), k + (dk-1)) and returns C(n,k)

base offset map
    |0b00      |0b01       |0b10       |dk axis
------------------------------------------------
0b00|n-1,k-1   |n-1,k      |n-1,k+1    |
0b01|n  ,k-1   |n  ,k      |n  ,k+1    |
0b10|n+1,k-1   |n+1,k      |n+1,k+1    |
dn axis
*/

static inline uint64_t step(uint64_t base, uint32_t n, uint32_t k, uint32_t dn, uint32_t dk) {
    switch (dn << 2 | dk) {
    case 0b0000:  // up left
        return base * (k + 1) / (n + 1);
    case 0b0001:  // up
        return base * (n - k + 1) / (n + 1);
    case 0b0010:  // up right
        return (base * (n - k + 1) * (n - k + 2)) / (k * (n + 1));
    case 0b0100:  // left
        return base * (k + 1) / (n - k);
    case 0b0101:  // center
        return base;
    case 0b0110:  // right
        return base * (n - k + 1) / k;
    case 0b1000:  // down left
        return (base * (k + 1) * n) / ((n - k) * (n - k - 1));
    case 0b1001:  // down
        return base * n / (n - k);
    case 0b1010:  // down right
        return base * n / k;
    default:
        __builtin_unreachable();
    }
}

__attribute__((noinline)) static uint64_t binomial(uint32_t n, uint32_t k) {
    // assert(n <= 33 and 2 * k <= n);
    k = min(k, n - k);
    switch (k) {
    // trivial cases
    case 0:
        return 1;
    case 1:
        return n;
    case 2:
        return n * (n - 1) / 2;
    // sparse hexagonal anchor table lookup with 0-2 multiplicative steps
    default:

        if (2 * k == n) {  // central line laverage simetry reducing 2 step case to 1 step
            int32_t xr = (static_cast<int32_t>(n) - 8) % 3, xa = (static_cast<int32_t>(n) - 8) / 3;
            switch (xr) {
            case -2:  // last pre anchor value
                return 20;
            case 0:  // anchor hit
                return anchors[Tri_xy_to_idx(xa, xa / 2)];
            case 1:  // right + simetry additiv down
                return static_cast<uint64_t>(anchors[Tri_xy_to_idx(xa, xa / 2)]) * (n + 1 - k) / (k - 1) * 2;
            case 2:  // down + simetry additive down
                return static_cast<uint64_t>(anchors[Tri_xy_to_idx(xa, xa / 2)]) * (n - 1) / k * 2;
            }
        } else {
            uint32_t xa = (n - 7u) / 3u, xr = (n - 7u) % 3u;
            uint32_t ya = (k - 3u) / 3u, yr = (k - 3u) % 3u;
            return step(anchors[Tri_xy_to_idx(xa, ya)], n, k, xr, yr);
        }
        __builtin_unreachable();
    }
}

int main() {
#ifdef LOCAL_DEBUG
    ifstream fin("test_input.txt");
    ofstream fout("result.txt");
#define cin fin
#define cout fout
#endif
    // int cnt = 0;
    cout << binomial(33, 13) << '\n';
    for (int i = 0; i <= 12; i++) {
        for (int j = 0; j <= i; j++) {
            // cnt++;
            cout << binomial(i, j) << '\t';
        }
        cout << '\n';
    }
    // cout << cnt << '\n';
    return 0;
}