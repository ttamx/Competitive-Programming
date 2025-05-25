#include <cstdio>
#include <cassert>
#include <vector>
#include "fence.cpp"

int main() {
  static int N, M, Q, A, B;
  static std::vector<std::vector<int>> LL, UR, P;
  static std::vector<int> H;
  scanf("%d %d %d", &N, &M, &Q); 
  LL.assign(N, std::vector<int>(2)); 
  UR.assign(N, std::vector<int>(2));
  H.resize(N);
  P.assign(M, std::vector<int>(2));
  for (int i = 0; i < N; ++i) {
    scanf("%d %d %d %d %d", &LL[i][0], &LL[i][1], &UR[i][0], &UR[i][1], &H[i]);
  }
  for (int i = 0; i < M; ++i) {
    scanf("%d %d", &P[i][0], &P[i][1]);
  }
  init(N, M, LL, UR, H, P);
  while (Q--) {
    scanf("%d %d", &A, &B);
    printf("%lld\n", ask(A, B));
  } 
}

// [[1, 10], [6, 3], [5, 2], [9, 6], [18, 16], [4, 1]]
// [[3, 14], [8, 4], [13, 12], [12, 8], [20, 18], [17, 13]]
// [10, 5, 7, 19, 6, 1]
// [[2, 11], [7, 9], [11, 7], [14, 5], [19, 17]]

/*
6 5 3
1 10 3 14 10 
6 3 8 4 5
5 2 13 12 7
9 6 12 8 19
18 16 20 18 6
4 1 17 13 1
2 11
7 9
11 7
14 5
19 17
*/