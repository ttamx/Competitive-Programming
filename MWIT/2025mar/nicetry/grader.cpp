#include "nicetry.cpp"
#include <cassert>
#include <cstdio>
#include <vector>

int main (int argc, char *argv[]) {
  int N, Q;
  assert(scanf("%d %d", &N, &Q) == 2);

  std::vector<int> A(N), B(N), C(N);
  for (int i = 0; i < N; i++) {
    assert(scanf("%d", &A[i]) == 1);
  }
  for (int i = 0; i < N; i++) {
    assert(scanf("%d", &B[i]) == 1);
  }
  for (int i = 0; i < N; i++) {
    assert(scanf("%d", &C[i]) == 1);
  }

  init(N, Q, A, B, C);

  while (Q--) {
    int a, b, c;
    assert(scanf("%d %d %d", &a, &b, &c) == 3);
    printf("%lld\n", find_order(a, b, c));
  }
  return 0;
}
