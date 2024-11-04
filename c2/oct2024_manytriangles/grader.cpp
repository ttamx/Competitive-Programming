#include "manytriangles.cpp"
#include <cassert>
#include <cstdio>
#include <tuple>
#include <vector>

int main() {
    int n;
    assert(scanf("%d", &n));
    std::vector<int> xs, ys;
    xs.reserve(3 * n);
    ys.reserve(3 * n);
    for (int i = 0; i < 3 * n; i++) {
        int x, y;
        assert(scanf("%d%d", &x, &y));
        xs.push_back(x);
        ys.push_back(y);
    }
    long long ans = mincost_color(n, xs, ys);
    printf("%lld\n", ans);
    return 0;
}