#include "bombs.cpp"
#include <cassert>
#include <cstdio>
#include <tuple>
#include <vector>

int main() {
  static int n;
  static std::vector<std::tuple<int, int, int, int>> query;
  assert(scanf("%d", &n) == 1);
  for (int i = 0, a, b, c, d; i < n; ++i) {
    assert(scanf("%d %d %d %d", &a, &b, &c, &d) == 4);
    query.emplace_back(a, b, c, d);
  }
  initialize(n);
  for (const auto q : query) {
    int a,b,c,d;
    std::tie(a,b,c,d) = q;
    printf("%lld\n", max_hp_loss(a, b, c, d));
  }
  return 0;
}
