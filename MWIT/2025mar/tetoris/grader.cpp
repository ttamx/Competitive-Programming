#include "tetoris.cpp"
#include <cstdio>
#include <cassert>
#include <vector>

int main() {
    int N, Q;
    assert(scanf("%d %d", &N, &Q) == 2);

    std::vector<int> X(N);
    for (int i = 0; i < N; i++) {
        assert(scanf("%d", &X[i]) == 1);
    }

    init(N, Q, X);

    while (Q--) {
        long long Y;
        assert(scanf("%lld", &Y) == 1);
        printf("%lld\n", miku_ask(Y));
    }

    return 0;
}
