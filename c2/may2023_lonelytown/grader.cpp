#include "lonelytown.cpp"
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdio>
#include <algorithm>

int main() {
    int N, Q;
    assert(scanf("%d %d", &N, &Q) == 2);
    assert(N >= 2 && Q >= 2);

    std::vector<int> u(N - 1), v(N - 1);

    for(int i=0; i<N-1; i++) {
        assert(scanf("%d %d", &u[i], &v[i]) == 2);
        assert(u[i] != v[i]);
    }

    init_town(N, Q, u, v);

    for(int i=0; i<Q; i++) {
        int t;
        assert(scanf("%d", &t) == 1);
        assert(t >= 1 && t <= 3);

        switch(t) {
            case 1 : {
                int x, y, z;
                assert(scanf("%d %d %d", &x, &y, &z) == 3);
                assert(std::min({x, y, z}) >= 0 && std::max({x, y, z}) < N);
                change_edge(x, y, z);
                break;
            }
            case 2 : {
                printf("%d\n", lonelytown_query());
                break;
            }
            case 3 : {
                int e;
                assert(scanf("%d", &e) == 1);
                assert(e >= 0 && e < N-1);
                printf("%d\n", simulate_query(e));
                break;
            }
            default : break;
        }
    }

    return 0;

}