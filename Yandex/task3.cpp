
#include <iostream>
#include<string>
#include<algorithm>

typedef unsigned long long  ul;
struct point {
    ul a, b;
    point(ul a, ul b) :a(a), b(b) {}
};

struct cmp {
    inline bool operator()(const point& l, const point& r) {
        return l.a < r.a;
    }
};

int main() {
    ul N;
    std::cin >> N;
    point* points = reinterpret_cast<point*>(malloc(sizeof(point) * N));
    ul a, b;
    for (ul i = 0; i < N; ++i) {
        std::cin >> a >> b;
        points[i] = point(a, b);
    }

    std::sort(points, points + N, cmp());

    ul* right_min = new ul[N + 1];
    ul x = 2 * N + 1;
    right_min[N] = x;
    for (ul i = N; i-- > 0;) {//итерация от N-1 до 0 без underflow
        x = std::min(x, points[i].b);
        right_min[i] = x;
    }

    ul cnt = 0;
    x = 0;
    for (ul i = 0; i < N; i++) {
        b = points[i].b;
        cnt += (x < b) && (b < right_min[i + 1]);
        x = std::max(x, b);
    }

    std::cout << cnt << std::endl;
    return 0;
}
