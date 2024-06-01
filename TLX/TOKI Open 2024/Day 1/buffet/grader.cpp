#include "buffet.cpp"

#include <cassert>
#include <cstdio>
#include <vector>

int main() {
  int N;
  assert(1 == scanf("%d", &N));

  std::vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &A[i]));
  }

  long long result = min_leftover(N, A);
  printf("%lld\n", result);
  return 0;
}
