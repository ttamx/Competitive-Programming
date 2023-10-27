#include "updown_sub7.cpp"
#include <cstdio>
#include <vector>
using namespace std;

int main() {
  int N, M;
  scanf("%d%d", &N, &M);
  vector<int> U, V;
  U.reserve(M);
  V.reserve(M);
  for (int i = 0; i < M; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    U.push_back(u);
    V.push_back(v);
  }
  vector<int> out = updown(N, M, U, V);
  for (int x : out) {
    printf("%d\n", x);
  }
  return 0;
}