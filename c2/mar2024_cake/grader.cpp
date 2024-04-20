#include <iostream>
#include <vector>

#include "cake.cpp"

signed main(int argc, char *argv[]) {
  int N, M;
  std::cin >> N >> M;
  std::vector<int> X(N), Y(N);
  for(int i=0; i<N; ++i) {
    std::cin >> X[i] >> Y[i];
  }
  std::cout << whipped_cream_price(N, M, X, Y) << "\n";
  return 0;
}
