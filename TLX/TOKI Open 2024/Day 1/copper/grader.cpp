#include "copper.cpp"

#include <cassert>
#include <cstdio>
#include <vector>

int main() {
  int N, M, L;
  assert(3 == scanf("%d %d %d", &N, &M, &L));

  std::vector<int> U(N - 1), V(N - 1);
  for (int i = 0; i < N - 1; ++i) {
    assert(2 == scanf("%d %d", &U[i], &V[i]));
  }

  std::vector<int> A(M);
  for (int i = 0; i < M; i++) {
    assert(1 == scanf("%d", &A[i]));
  }

  std::vector<int> S(L);
  for (int i = 0; i < L; i++) {
    assert(1 == scanf("%d", &S[i]));
  }

  long long result = min_risk(N, M, L, U, V, A, S);
  printf("%lld\n", result);
  return 0;
}
