#include "colorful.cpp"
#include <cstdio>

int main() {
  int n, m, k, q;
  scanf("%d%d%d%d", &n, &m, &k, &q);
  std::vector<int> x, y;
  x.reserve(m);
  y.reserve(m);
  for (int i = 0; i < m; i++) {
    int xi, yi;
    scanf("%d%d", &xi, &yi);
    x.push_back(xi);
    y.push_back(yi);
  }
  init_machine(n, m, k, q, x, y);
  for (int i = 0; i < q; i++) {
    int c, s;
    long long t;
    scanf("%d%d%lld", &c, &s, &t);
    int ans = send_ball(c, s, t);
    printf("%d\n", ans);
  }
  return 0;
}
