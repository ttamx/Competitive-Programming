#include "compatibility.cpp"
#include <cassert>
#include <cstdio>

int main() {
  int m, n;
  assert(scanf("%d%d", &m, &n) > 0);
  std::vector<std::vector<int>> objects;
  for (int i = 0; i < m; i++) {
    std::vector<int> object;
    object.reserve(n);
    for (int j = 0; j < n; j++) {
      int x;
      assert(scanf("%d", &x) > 0);
      object.push_back(x);
    }
    objects.push_back(object);
  }
  long long output = maximum_incompatibility(objects);
  printf("%lld\n", output);
  return 0;
}