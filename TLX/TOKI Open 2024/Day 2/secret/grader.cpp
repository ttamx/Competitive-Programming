#include "secret.cpp"

#include <cassert>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>


int main() {
  int N, M, Q;
  assert(3 == scanf("%d %d %d", &N, &M, &Q));

  std::vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    assert(1 == scanf("%d", &A[i]));
  }

  init(N, M, A);
  
  for (int i = 0; i < Q; i++) {
    int type;
    assert(1 == scanf("%d", &type));
    if (type == 0) {
      int R;
      assert(1 == scanf("%d", &R));
      toggle(R);
    } else if (type == 1) {
      int S, T;
      assert(2 == scanf("%d %d", &S, &T));
      printf("%lld\n", query(S, T));
    }
  }
  return 0;
}
