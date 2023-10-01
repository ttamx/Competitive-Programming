#include <cstdio>
#include <cstdlib>
#include <vector>
#include "seats.cpp"

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
  int H = read_int();
  int W = read_int();
  int Q = read_int();
  std::vector<int> R(H * W), C(H * W);
  for (int i = 0; i < H * W; ++i) {
    R[i] = read_int();
    C[i] = read_int();
  }
  std::vector<int> A(Q), B(Q);
  for (int j = 0; j < Q; ++j) {
    A[j] = read_int();
    B[j] = read_int();
  }

  give_initial_chart(H, W, R, C);
  for (int j = 0; j < Q; ++j) {
    int answer = swap_seats(A[j], B[j]);
    printf("%d\n", answer);
  }
  return 0;
}
