#include "swap.cpp"

#include <cassert>
#include <cstdio>

#include <string>
#include <vector>

int main() {
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));
  
  std::vector<int> U(M), V(M), W(M);
  for (int i = 0; i < M; ++i) {
    assert(3 == scanf("%d %d %d", &U[i], &V[i], &W[i]));
  }

  int Q;
  assert(1 == scanf("%d", &Q));

  std::vector<int> X(Q), Y(Q);
  for (int i = 0; i < Q; ++i) {
    assert(2 == scanf("%d %d", &X[i], &Y[i]));
  }

  init(N, M, U, V, W);
  
  std::vector<int> minimum_fuel_capacities(Q);
  for (int i = 0; i < Q; ++i) {
    minimum_fuel_capacities[i] = getMinimumFuelCapacity(X[i], Y[i]);
  }

  for (int i = 0; i < Q; ++i) {
    printf("%d\n", minimum_fuel_capacities[i]);
  }
  
  return 0;
}
