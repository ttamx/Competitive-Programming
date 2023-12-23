#include "closing.cpp"

#include <cassert>
#include <cstdio>

#include <vector>

int main()
{

    int Q;
    assert(1 == scanf("%d", &Q));

    std::vector<int> N(Q), X(Q), Y(Q);
    std::vector<long long> K(Q);
    std::vector<std::vector<int>> U(Q), V(Q), W(Q);

    for (int q = 0; q < Q; q++)
    {
        assert(4 == scanf("%d %d %d %lld", &N[q], &X[q], &Y[q], &K[q]));

        U[q].resize(N[q] - 1);
        V[q].resize(N[q] - 1);
        W[q].resize(N[q] - 1);
        for (int i = 0; i < N[q] - 1; ++i)
        {
            assert(3 == scanf("%d %d %d", &U[q][i], &V[q][i], &W[q][i]));
        }
    }
    fclose(stdin);

    std::vector<int> result(Q);
    for (int q = 0; q < Q; q++)
    {
        result[q] = max_score(N[q], X[q], Y[q], K[q], U[q], V[q], W[q]);
    }

    for (int q = 0; q < Q; q++)
    {
        printf("%d\n", result[q]);
    }
    fclose(stdout);

    return 0;
}
