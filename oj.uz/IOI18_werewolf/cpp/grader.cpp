#include <cstdio>
#include <cstdlib>
#include <vector>
#include "werewolf.cpp"

namespace {

int read_int() {
  int x;
  if (scanf("%d", &x) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  return x;
}

}  // namespace

int main() {
  int N = read_int();
  int M = read_int();
  int Q = read_int();
  std::vector<int> X(M), Y(M), S(Q), E(Q), L(Q), R(Q);
  for (int j = 0; j < M; ++j) {
    X[j] = read_int();
    Y[j] = read_int();
  }
  for (int i = 0; i < Q; ++i) {
    S[i] = read_int();
    E[i] = read_int();
    L[i] = read_int();
    R[i] = read_int();
  }

  std::vector<int> A = check_validity(N, X, Y, S, E, L, R);
  for (size_t i = 0; i < A.size(); ++i) {
    printf("%d\n", A[i]);
  }
  return 0;
}
