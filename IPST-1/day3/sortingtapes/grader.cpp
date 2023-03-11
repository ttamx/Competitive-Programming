#include "sortingtapes.cpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

int last_p = -1, last_q = -1, n;
long long cost = 0;
vector<int> x, ans, next_num;

bool compare(int p, int q) {
  if (last_p != -1) {
    cost += abs(p - last_p) + abs(q - last_q);
  }
  assert(0 <= p && p < n);
  assert(n <= q && q < 2 * n);
  last_p = p;
  last_q = q;

  return x[p] < x[q];
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n;

  x = vector<int>(2 * n);
  ans = vector<int>(2 * n);
  for (int i = 0; i < 2 * n; ++i) {
    cin >> x[i];
  }
  iota(ans.begin(), ans.end(), 0);
  sort(ans.begin(), ans.end(), [&](int p, int q) { return x[p] < x[q]; });

  next_num = vector<int>(2 * n, -1);
  for (int i = 0; i < 2 * n - 1; ++i) {
    next_num[ans[i]] = ans[i + 1];
  }

  vector<int> a(n), b(n);
  iota(a.begin(), a.end(), 0);
  iota(b.begin(), b.end(), n);
  sort(a.begin(), a.end(), [&](int p, int q) { return x[p] < x[q]; });
  sort(b.begin(), b.end(), [&](int p, int q) { return x[p] < x[q]; });

  vector<int> c = sort_tapes(n, a, b);

  cout << cost << "\n";
  for (int i = 0; i < c.size(); ++i) {
    cout << c[i];
    if (i != c.size() - 1)
      cout << " ";
  }
  cout << "\n";
}
