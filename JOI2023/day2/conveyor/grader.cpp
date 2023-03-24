#include "conveyor.h"
#include <bits/stdc++.h>

using namespace std;

namespace {

const int INVALID_X_LENGTH = 1;
const int INVALID_X_RANGE = 2;
const int INVALID_Y_LENGTH = 3;
const int INVALID_Y_RANGE = 4;
const int QUERY_LIMIT_EXCEEDED = 5;
const int INVALID_A_LENGTH = 6;
const int INVALID_A_RANGE = 7;
const int WRONG_A = 8;
const int ANSWER_TWICE = 9;
const int NO_ANSWER = 10;

const int QUERY_LIMIT = 30;

int N;
std::vector<int> A, B, C;

int query_count = 0;
bool answered = false;

void WrongAnswer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(0);
}

std::mt19937 rng(0);

int random_select(const std::vector<int> &v) {
  return v[std::uniform_int_distribution<int>(0, v.size() - 1)(rng)];
}

} // namespace

std::vector<int> Query(std::vector<int> x, std::vector<int> y) {
  if (int(x.size()) != N - 1) {
    WrongAnswer(INVALID_X_LENGTH);
  }
  for (int i = 0; i < N - 1; i++) {
    if (x[i] != 0 && x[i] != 1) {
      WrongAnswer(INVALID_X_RANGE);
    }
  }
  if (int(y.size()) != N) {
    WrongAnswer(INVALID_Y_LENGTH);
  }
  for (int i = 0; i < N; i++) {
    if (y[i] != 0 && y[i] != 1) {
      WrongAnswer(INVALID_Y_RANGE);
    }
  }
  query_count++;
  if (query_count > QUERY_LIMIT) {
    WrongAnswer(QUERY_LIMIT_EXCEEDED);
  }
  std::vector<int> z(N, 0);
  std::vector<std::vector<int>> t(N);
  for (int i = 0; i < N - 1; i++) {
    int a = A[i], b = B[i];
    if (x[i] ^ C[i]) {
      std::swap(a, b);
    }
    t[a].push_back(b);
  }
  for (int i = 0; i < N; i++) {
    if (y[i]) {
      if (t[i].empty()) {
        z[i] = 1;
      } else {
        z[random_select(t[i])] = 1;
      }
    }
  }
  return z;
}

void Answer(std::vector<int> a) {
  if (answered) {
    WrongAnswer(ANSWER_TWICE);
  }
  answered = true;
  if (int(a.size()) != N - 1) {
    WrongAnswer(INVALID_A_LENGTH);
  }
  for (int i = 0; i < N - 1; i++) {
    if (a[i] != 0 && a[i] != 1) {
      WrongAnswer(INVALID_A_RANGE);
    }
  }
  if (a != C) {
    for(auto x:a)cerr << x << ' ';
    WrongAnswer(WRONG_A);
  }
}

int main(int argc, char **argv) {
  if (argc >= 2) {
    long long seed = atoll(argv[1]);
    rng.seed(seed);
  }

  if (scanf("%d", &N) != 1) {
    fprintf(stderr, "Error while reading input.\n");
    exit(1);
  }
  A.resize(N - 1);
  B.resize(N - 1);
  C.resize(N - 1);
  for (int i = 0; i < N - 1; i++) {
    if (scanf("%d", &A[i]) != 1) {
      fprintf(stderr, "Error while reading input.\n");
      exit(1);
    }
  }
  for (int i = 0; i < N - 1; i++) {
    if (scanf("%d", &B[i]) != 1) {
      fprintf(stderr, "Error while reading input.\n");
      exit(1);
    }
  }
  for (int i = 0; i < N - 1; i++) {
    if (scanf("%d", &C[i]) != 1) {
      fprintf(stderr, "Error while reading input.\n");
      exit(1);
    }
  }
  Solve(N, A, B);
  if (!answered) {
    WrongAnswer(NO_ANSWER);
  }
  printf("Accepted: %d\n", query_count);
  return 0;
}