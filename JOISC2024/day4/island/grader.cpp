#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <utility>
#include <vector>

#include "island.cpp"

namespace {

const int invalid_v_range = 1;
const int invalid_k_range = 2;
const int query_limit_exceeded = 3;
const int invalid_xy_range = 4;
const int no_edge = 5;
const int answer_twice = 6;
const int invalid_answer_times = 7;

int N, L, ok;
std::vector<int> A, B, answered;
std::vector<std::vector<int>> g, dist, que;
std::vector<std::pair<int, int>> p;

int query_count = 0;
int answer_count = 0;

void wronganswer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(0);
}

void dfs(int now, int pre, std::vector<std::vector<int>> &g,
         std::vector<int> &dist) {
  for (int nxt : g[now]) {
    if (nxt == pre) {
      continue;
    }
    dist[nxt] = dist[now] + 1;
    dfs(nxt, now, g, dist);
  }
}

}  // namespace

int query(int v, int k) {
  if (v < 1 || N < v) {
    wronganswer(invalid_v_range);
  }
  if (k < 1 || N - 1 < k) {
    wronganswer(invalid_k_range);
  }

  query_count++;
  if (query_count > L) {
    wronganswer(query_limit_exceeded);
  }

  return que[v - 1][k] + 1;
}

void answer(int x, int y) {
  if (x < 1 || N < x || y < 1 || N < y) {
    wronganswer(invalid_xy_range);
  }
  if (x > y) {
    std::swap(x, y);
  }

  answer_count++;
  if (answer_count > N - 1) {
    wronganswer(invalid_answer_times);
  }

  ok = -1;
  for (int i = 0; i < N - 1; i++) {
    if (A[i] == x && B[i] == y) {
      if (answered[i] != 0) {
        wronganswer(answer_twice);
      }
      ok = i;
    }
  }

  if (ok == -1) {
    wronganswer(no_edge);
  }

  answered[ok] = 1;
}

int main(int argc, char **argv) {
  if (scanf("%d", &N) != 1) {
    fprintf(stderr, "Error while reading input.\n");
    exit(1);
  }
  if (scanf("%d", &L) != 1) {
    fprintf(stderr, "Error while reading input.\n");
    exit(1);
  }

  A.resize(N - 1);
  B.resize(N - 1);
  answered.resize(N - 1, 0);
  g.resize(N);
  dist.resize(N, std::vector<int>(N));
  que.resize(N);

  for (int i = 0; i < N - 1; i++) {
    if (scanf("%d", &A[i]) != 1) {
      fprintf(stderr, "Error while reading input.\n");
      exit(1);
    }
    if (scanf("%d", &B[i]) != 1) {
      fprintf(stderr, "Error while reading input.\n");
      exit(1);
    }
  }
  for (int i = 0; i < N - 1; i++) {
    if (A[i] >= B[i]) {
      std::swap(A[i], B[i]);
    }
    g[A[i] - 1].emplace_back(B[i] - 1);
    g[B[i] - 1].emplace_back(A[i] - 1);
  }

  for (int i = 0; i < N; i++) {
    dist[i][i] = 0;
    dfs(i, -1, g, dist[i]);

    p.clear();
    for (int j = 0; j < N; j++) {
      p.emplace_back(dist[i][j], j);
    }
    std::sort(p.begin(), p.end());

    for (int j = 0; j < N; j++) {
      que[i].emplace_back(p[j].second);
    }
  }

  solve(N, L);
  if (answer_count != N - 1) {
    wronganswer(invalid_answer_times);
  }
  printf("Accepted: %d\n", query_count);
  return 0;
}