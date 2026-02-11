#include <iostream>
#include <bitset>
#include <fstream>
#include <array>
#include <cassert>
using namespace std;
int main() {
#ifdef LOCAL_DEBUG
    ifstream fin("test_input.txt");
#define cin fin  // Redirect cin to read from the file
#endif

    unsigned short N, M;
    int i, j;
    array<bitset<100>, 100> dir{};
    // 0 - from left
    // 1 - from up
    cin >> N >> M;
    union {
        array<unsigned short, 100> sums;
        array<char, 400> answer;
    } data{};
    short val;

    cin >> data.sums[0];
    for (i = 1; i < M; ++i) {
        cin >> val;
        data.sums[i] = data.sums[i - 1] + val;
    }

    for (j = 1; j < N; ++j) {
        cin >> val;
        data.sums[0] += val;
        dir[j][0] = true;

        for (i = 1; i < M; ++i) {
            cin >> val;
            if (data.sums[i] > data.sums[i - 1]) {
                data.sums[i] += val;
                dir[j][i] = true;
            } else {
                data.sums[i] = data.sums[i - 1] + val;
            }
        }
    }
    cout << data.sums[M - 1] << '\n';

    // Backtrack & single buffer string backing
    j = N - 1;
    i = M - 1;
    data.answer[(i + j) * 2] = '\0';
    while (i or j) {
        if (dir[j][i]) {
            --j;
            data.answer[(i + j) * 2] = 'D';
        } else {
            --i;
            data.answer[(i + j) * 2] = 'R';
        }
        data.answer[(i + j) * 2 + 1] = ' ';

        assert(i >= 0 and j >= 0);
    }
    cout << reinterpret_cast<char*>(&data.answer);
    return 0;
}