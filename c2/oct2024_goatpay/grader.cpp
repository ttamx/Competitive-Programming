#include "goatpay.cpp"
#include <iostream>
#include <vector>

signed main(int argc, char *argv[]) {
  int N, Q;
  std::cin >> N >> Q;
  std::vector<int> U, V, C;
  std::vector<int> W;
  for(int i=2, u, v, w, c; i<=N; ++i) {
    std::cin >> u >> v >> w >> c;
    U.emplace_back(u);
    V.emplace_back(v);
    W.emplace_back(w);
    C.emplace_back(c);
  }
  plant_tree(N, U, V, W, C);
  while(Q--) {
    int type;
    std::cin >> type;
    if(type == 1) {
      int u, v, x;
      std::cin >> u >> v >> x;
      std::cout << goat_pay(u, v, x) << "\n";
    }
    else {
      int id, d;
      std::cin >> id >> d;
      update_edge(id, d);
    }
  }
  return 0;
}