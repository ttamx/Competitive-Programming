#include "overtaking.cpp"
#include <cassert>
#include <cstdio>
#include <vector>

int main()
{
    int L, N, X, M, Q;
    assert(5 == scanf("%d %d %d %d %d", &L, &N, &X, &M, &Q));
    std::vector<long long> T(N);
    for (int i = 0; i < N; i++)
        assert(1 == scanf("%lld", &T[i]));
    std::vector<int> W(N);
    for (int i = 0; i < N; i++)
        assert(1 == scanf("%d", &W[i]));
    std::vector<int> S(M);
    for (int i = 0; i < M; i++)
        assert(1 == scanf("%d", &S[i]));
    std::vector<long long> Y(Q);
    for (int i = 0; i < Q; i++)
        assert(1 == scanf("%lld", &Y[i]));

    fclose(stdin);

    init(L, N, T, W, X, M, S);
    std::vector<long long> res(Q);
    for (int i = 0; i < Q; i++)
        res[i] = arrival_time(Y[i]);

    for (int i = 0; i < Q; i++)
        printf("%lld\n", res[i]);
    fclose(stdout);
    return 0;
}
