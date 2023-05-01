#include "expensive.cpp"
#include <cassert>
#include <cstdio>

int main(int argc, char *argv[]) {
  int N, Q;
  assert(scanf("%d%d", &N, &Q) > 0);
  std::vector<int> C;
  std::vector<std::pair<int, int>> R;
  R.reserve(N - 1);
  C.reserve(N - 1);
  for (int i = 1; i < N; i++) {
    int ui, vi, wi;
    assert(scanf("%d%d%d", &ui, &vi, &wi) > 0);
    R.push_back({ui, vi});
    C.push_back(wi);
  }
  initialize(N, Q, R, C);
  for (int i = 0; i < Q; i++) {
    int a, b;
    assert(scanf("%d%d", &a, &b) > 0);
    printf("%lld\n", most_expensive(a, b));
  }
  return 0;
}