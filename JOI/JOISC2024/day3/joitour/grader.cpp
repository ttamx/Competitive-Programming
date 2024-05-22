#include <cassert>
#include <cstdio>

#include "joitour.cpp"

int main() {
  int N;
  assert(scanf("%d", &N) == 1);

  std::vector<int> F(N);
  for (int i = 0; i < N; i++) {
    assert(scanf("%d", &F[i]) == 1);
  }

  std::vector<int> U(N - 1), V(N - 1);
  for (int j = 0; j < N - 1; j++) {
    assert(scanf("%d %d", &U[j], &V[j]) == 2);
  }

  int Q;
  assert(scanf("%d", &Q) == 1);

  init(N, F, U, V, Q);
  printf("%lld\n", num_tours());
  fflush(stdout);

  for (int k = 0; k < Q; k++) {
    int X, Y;
    assert(scanf("%d %d", &X, &Y) == 2);

    change(X, Y);
    printf("%lld\n", num_tours());
    fflush(stdout);
  }
}
