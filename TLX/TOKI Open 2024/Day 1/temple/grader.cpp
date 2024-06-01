#include "temple.cpp"

#include <cassert>
#include <cstdio>
#include <vector>

int main() {
  int N, M, K;
  assert(3 == scanf("%d %d %d", &N, &M, &K));

  std::vector<int> U(M), V(M), W(M);
  for (int i = 0; i < M; i++) {
    assert(3 == scanf("%d %d %d", &U[i], &V[i], &W[i]));
  }

  std::vector<int> P(K);
  for (int i = 0; i < K; i++) {
    assert(1 == scanf("%d", &P[i]));
  }

  long long res = min_weight(N, M, K, U, V, W, P);

  printf("%lld\n", res);
  return 0;
}
