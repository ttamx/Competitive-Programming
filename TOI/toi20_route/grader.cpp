#include <cassert>
#include <cstdio>
#include <vector>
#include <utility>

#include "route.cpp"

int main() {
  int N;
  assert(scanf("%d", &N) == 1);

  int M;
  assert(scanf("%d", &M) == 1);

  std::vector<int> W(M);
  for (int i = 0; i < M; i++) {
    assert(scanf("%d", &W[i]) == 1);
  }

  std::vector<std::pair<int, int>> V = route(N, W);

  for (int j = 0; j < M; j++) {
    printf("%d %d %d\n", V[j].first, V[j].second, W[j]);
    fflush(stdout);
  }
}
