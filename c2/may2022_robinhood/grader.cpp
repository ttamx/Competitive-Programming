#include "robinhood.cpp"
#include <cassert>
#include <cstdio>
#include <utility>
#include <vector>


int main() {
  static int N, M;
  static std::vector<int> A;
  static std::vector<std::pair<int, int>> query;
  assert(scanf("%d %d", &N, &M) == 2);
  for (int i = 0, v; i < N; ++i) {
    scanf("%d", &v);
    A.emplace_back(v);
  }
  for (int i = 0, a, b; i < M; ++i) {
    scanf("%d %d", &a, &b);
    assert(a == 1 or a == 2);
    assert(b >= 0 and b < N);
    query.emplace_back(a, b);
  }
  initialize(A, M);
  for (auto [a, b] : query) {
    if (a == 1)
      add(b);
    else
      printf("%d\n", ask(b));
  }
  return 0;
}