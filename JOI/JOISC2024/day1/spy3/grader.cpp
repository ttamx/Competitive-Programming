#include <cstdio>
#include <cstdlib>

#include "Aoi.h"
#include "Bitaro.h"

namespace {

constexpr int S_LIMIT = 12'000;

int N;
int M;
int Q;
int K;
std::vector<int> A;
std::vector<int> B;
std::vector<long long> C;
std::vector<int> T;
std::vector<int> X;

std::vector<long long> C_bitaro;

int answer_count = 0;
std::vector<long long> results;

void wrong_answer(int code) {
  fprintf(stderr, "Wrong Answer [%d]\n", code);
  exit(0);
}

}  // namespace

int main(int argc, char **argv) {
  if (scanf("%d%d", &N, &M) != 2) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  A.resize(M);
  B.resize(M);
  C.resize(M);
  for (int i = 0; i < M; i++) {
    if (scanf("%d%d%lld", &A[i], &B[i], &C[i]) != 3) {
      fprintf(stderr, "Error while reading input\n");
      exit(1);
    }
  }
  if (scanf("%d", &Q) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  T.resize(Q);
  for (int i = 0; i < Q; i++) {
    if (scanf("%d", &T[i]) != 1) {
      fprintf(stderr, "Error while reading input\n");
      exit(1);
    }
  }
  if (scanf("%d", &K) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  X.resize(K);
  for (int i = 0; i < K; i++) {
    if (scanf("%d", &X[i]) != 1) {
      fprintf(stderr, "Error while reading input\n");
      exit(1);
    }
  }
  std::string s = aoi(N, M, Q, K, A, B, C, T, X);

  for (const char c : s) {
    if (!(c == '0' || c == '1')) wrong_answer(1);
  }
  if (!((int)s.size() <= S_LIMIT)) wrong_answer(2);
  C_bitaro = C;
  for (const int x : X) {
    C_bitaro[x] = -1;
  }
  bitaro(N, M, Q, K, A, B, C_bitaro, T, X, s);
  if (answer_count != Q) wrong_answer(6);
  fprintf(stderr, "Accepted: %zu\n", s.length());
  for (int i = 0; i < Q; i++) {
    printf("%lld\n", results[i]);
  }
  return 0;
}

void answer(const std::vector<int> &e) {
  if (answer_count >= Q) wrong_answer(6);
  int p = 0;
  long long d = 0;
  for (int t : e) {
    if (!(0 <= t && t <= M - 1)) {
      wrong_answer(3);
    }
    if (A[t] == p)
      p = B[t];
    else if (B[t] == p)
      p = A[t];
    else
      wrong_answer(4);
    d += C[t];
  }
  if (p != T[answer_count]) wrong_answer(4);
  results.push_back(d);
  answer_count++;
}