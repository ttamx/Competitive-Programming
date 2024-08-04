#include "Azer.cpp"
#include "Baijan.cpp"
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>

namespace {

const int MAX_L = 58000;

void WrongAnswer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(0);
}

int num_calls;
std::queue<bool> qx, qy;

}  // namespace

void SendA(bool y) {
  if (++num_calls > MAX_L) {
    WrongAnswer(2);
  }
  qy.push(y);
}

void SendB(bool x) {
  if (++num_calls > MAX_L) {
    WrongAnswer(2);
  }
  qx.push(x);
}

int main() {
  int N, A, B;
  if (scanf("%d%d%d", &N, &A, &B) != 3) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  std::vector<int> U(A), V(A), C(A), S(B), T(B), D(B);
  for (int i = 0; i < A; ++i) {
    if (scanf("%d%d%d", &U[i], &V[i], &C[i]) != 3) {
      fprintf(stderr, "Error while reading input\n");
      exit(1);
    }
  }
  for (int j = 0; j < B; ++j) {
    if (scanf("%d%d%d", &S[j], &T[j], &D[j]) != 3) {
      fprintf(stderr, "Error while reading input\n");
      exit(1);
    }
  }

  num_calls = 0;
  InitA(N, A, U, V, C);
  InitB(N, B, S, T, D);
  for (; ; ) {
    if (!qx.empty()) {
      ReceiveA(qx.front());
      qx.pop();
    } else if (!qy.empty()) {
      ReceiveB(qy.front());
      qy.pop();
    } else {
      break;
    }
  }
  std::vector<int> Z = Answer();
  if (Z.size() != static_cast<size_t>(N)) {
    WrongAnswer(1);
  }
  fprintf(stderr, "Accepted: %d\n", num_calls);
  for (int k = 0; k < N; ++k) {
    printf("%d\n", Z[k]);
  }
  return 0;
}
