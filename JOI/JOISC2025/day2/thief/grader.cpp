#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <bits/stdc++.h>

#include "thief.cpp"

namespace {

enum {
  INVALID_X_LENGTH = 1,
  INVALID_X_VALUE = 2,
  QUERY_LIMIT_EXCEEDED = 3,
  INVALID_A_VALUE = 4,
  INVALID_B_VALUE = 5,
  WRONG_ANSWER = 6,
  ANSWER_TWICE = 7,
  NO_ANSWER = 8,
};

const int QUERY_LIMIT = 300;
int QUERY_COUNT = 0;
int ANSWER_COUNT = 0;

int N, M, A, B;
std::vector<int> U, V;

std::vector<std::vector<std::pair<int, int>>> g;

void wrong_answer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(1);
}

}  // namespace

int query(std::vector<int> x) {
  QUERY_COUNT++;
  // for(auto v:x){
  //   std::cerr << v;
  // }
  // std::cerr << "\n";
  if (QUERY_COUNT > QUERY_LIMIT) {
    wrong_answer(QUERY_LIMIT_EXCEEDED);
  }
  if ((int)x.size() != M) {
    wrong_answer(INVALID_X_LENGTH);
  }
  for (int c : x) {
    if (c != 0 && c != 1) {
      wrong_answer(INVALID_X_VALUE);
    }
  }

  std::vector<int> q = {A};
  std::vector<bool> visited(N);
  visited[A] = 1;
  while (q.size()) {
    const int u = q.back();
    q.pop_back();
    for (auto [v, i] : g[u]) {
      if (visited[v]) continue;
      if (x[i % M] == i / M) {
        visited[v] = 1;
        q.push_back(v);
      }
    }
  }

  return visited[B];
}

void answer(int a, int b) {
  ANSWER_COUNT++;
  if (ANSWER_COUNT > 1) {
    wrong_answer(ANSWER_TWICE);
  }
  if (!(0 <= a && a < N)) {
    wrong_answer(INVALID_A_VALUE);
  }
  if (!(0 <= b && b < N)) {
    wrong_answer(INVALID_B_VALUE);
  }
  if (!(a == A && b == B)) {
    wrong_answer(WRONG_ANSWER);
  }
}

int main() {
  assert(scanf("%d%d%d%d", &N, &M, &A, &B) == 4);
  assert(N >= 0);
  assert(M >= 0);

  U.resize(M);
  V.resize(M);
  g.resize(N);

  for (int i = 0; i < M; i++) {
    int& u = U[i];
    int& v = V[i];
    assert(scanf("%d%d", &u, &v) == 2);

    if (!(0 <= u && u < N)) {
      fprintf(stderr, "Invalid value of U[%d]: %d\n", i, u);
      return 1;
    }
    if (!(0 <= v && v < N)) {
      fprintf(stderr, "Invalid value of V[%d]: %d\n", i, v);
      return 1;
    }

    g[u].emplace_back(v, i);
    g[v].emplace_back(u, M + i);
  }

  solve(N, M, U, V);

  if (ANSWER_COUNT == 0) {
    wrong_answer(NO_ANSWER);
  }
  printf("Accepted: %d\n", QUERY_COUNT);
}
