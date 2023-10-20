#include "islandparty.cpp"
#include <vector>
#include <cassert>
#include <cstdio>

int main() {
    int N, T;
    assert(scanf(" %d %d", &N, &T) == 2);
    std::vector<long long> A(N);
    std::vector<int> u(N - 1), v(N - 1), L(T), R(T), X(T);
    for (int i = 0; i < N; i++) {
        assert(scanf(" %lld", &A[i]) == 1);
    }
    for (int i = 0; i < N - 1; i++) {
        assert(scanf(" %d %d", &u[i], &v[i]) == 2);
    }

    init(N, T, A, u, v);

    for (int i = 0; i < T; i++) {
        assert(scanf(" %d %d %d", &L[i], &R[i], &X[i]) == 3);

        printf("%lld\n", find_drunkenness(L[i], R[i], X[i]));
    }
    return 0;
}
