#include "volunteers.cpp"
#include <ios>
#include <iostream>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int N, M, Q;
  std::cin >> N >> M >> Q;
  std::vector<std::vector<int>> H;
  H.resize(N);
  for (int i = 0; i < N; i++) {
    H[i].reserve(M);
    int x;
    for (int j = 0; j < M; j++) {
      std::cin >> x;
      H[i].push_back(x);
    }
  }
  setup_battalion(N, M, Q, H);
  while (Q--) {
    int L, R;
    std::cin >> L >> R;
    std::cout << count_volunteers(L, R) << "\n";
  }
  std::cout << std::flush;
  return 0;
}
