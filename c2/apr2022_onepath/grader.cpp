#include "onepath.cpp"
#include <vector>
#include <iostream>
#include <cassert>
#include <utility>

static int n1234, m1234, q1234;
static std::vector<std::pair<int, int>> r1234;
static std::vector<int> t1234;
static std::vector<std::pair<int, int>> f1234;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  assert(std::cin >> n1234 >> m1234 >> q1234);
  for (int i = 0, u, v; i < m1234; ++i) {
    assert(std::cin >> u >> v);
    r1234.emplace_back(u, v);
  }
  for (int i = 0, x, y, z; i < q1234; ++i) {
    assert(std::cin >> x >> y >> z);
    t1234.emplace_back(x);
    f1234.emplace_back(y, z);
  }
  initialize(n1234, m1234, q1234, r1234);
  std::vector<bool> answer;
  for (int i = 0; i < q1234; ++i) {
    if (t1234[i] == 1) {
      answer.emplace_back(is_dangerous(f1234[i].first, f1234[i].second));
    } else {
      build_road(f1234[i].first, f1234[i].second);
    }
  }
  for (auto ans : answer) {
    std::cout << (ans ? "true" : "false") << std::endl;
  }
}