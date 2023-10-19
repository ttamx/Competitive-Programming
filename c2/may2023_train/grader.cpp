/**
 * @author win11905
 */
#include "train.h"
#include <cassert>
#include <cstdio>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> u(n - 1), v(n - 1), a(m), b(m);
  for (int i = 0; i < n - 1; ++i) {
    scanf("%d %d", &u[i], &v[i]);
    assert(0 <= u[i] and u[i] < n);
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d %d", &a[i], &b[i]);
    assert(0 <= a[i] and a[i] < n);
  }
  printf("%d\n", train(n, m, u, v, a, b));
  return 0;
}