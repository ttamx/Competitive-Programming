#include "virus.cpp"
#include <cstdio>
#include <cassert>
#include <vector>
 
using namespace std;

static int NN, Q, X, Y;

int main() {
  assert(scanf("%d %d %d %d", &NN, &Q, &X, &Y) == 4);
  vector<int> vec(Q);
  for (int &L : vec) 
    assert(scanf("%d", &L) == 1);
  initialize(NN, X, Y);
  for (int L : vec)
    printf("%d\n", ask(L));
}
