#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
#include "highway.cpp"

namespace {

constexpr int MAX_NUM_CALLS = 100;
constexpr long long INF = 1LL << 61;

int NN, MM, A, B, S, T;
std::vector<int> U, V;
std::vector<std::vector<std::pair<int, int>>> graph;

bool answered, wrong_pair;
int num_calls;

int read_int() {
  int x;
  if (scanf("%d", &x) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  return x;
}

void wrong_answer(const char *MSG) {
  printf("Wrong Answer: %s\n", MSG);
  exit(0);
}

}  // namespace

long long ask(const std::vector<int> &w) {
  if (++num_calls > MAX_NUM_CALLS) {
    wrong_answer("more than 100 calls to ask");
  }
  if (w.size() != (size_t)MM) {
    wrong_answer("w is invalid");
  }
  for (size_t i = 0; i < w.size(); ++i) {
    if (!(w[i] == 0 || w[i] == 1)) {
      wrong_answer("w is invalid");
    }
  }

  std::vector<bool> visited(NN, false);
  std::vector<long long> current_dist(NN, INF);
  std::queue<int> qa, qb;
  qa.push(S);
  current_dist[S] = 0;
  while (!qa.empty() || !qb.empty()) {
    int v;
    if (qb.empty() ||
        (!qa.empty() && current_dist[qa.front()] <= current_dist[qb.front()])) {
      v = qa.front();
      qa.pop();
    } else {
      v = qb.front();
      qb.pop();
    }
    if (visited[v]) {
      continue;
    }
    visited[v] = true;
    long long d = current_dist[v];
    if (v == T) {
      return d;
    }
    for (auto e : graph[v]) {
      int vv = e.first;
      int ei = e.second;
      if (!visited[vv]) {
        if (w[ei] == 0) {
          if (current_dist[vv] > d + A) {
            current_dist[vv] = d + A;
            qa.push(vv);
          }
        } else {
          if (current_dist[vv] > d + B) {
            current_dist[vv] = d + B;
            qb.push(vv);
          }
        }
      }
    }
  }
  return -1;
}

void answer(int s, int t) {
  if (answered) {
    wrong_answer("answered not exactly once");
  }

  if (!((s == S && t == T) || (s == T && t == S))) {
    wrong_pair = true;
  }

  answered = true;
}

int main() {
  NN = read_int();
  MM = read_int();
  A = read_int();
  B = read_int();
  S = read_int();
  T = read_int();
  U.resize(MM);
  V.resize(MM);
  graph.assign(NN, std::vector<std::pair<int, int>>());
  for (int i = 0; i < MM; ++i) {
    U[i] = read_int();
    V[i] = read_int();
    graph[U[i]].push_back({V[i], i});
    graph[V[i]].push_back({U[i], i});
  }

  answered = false;
  wrong_pair = false;
  num_calls = 0;
  find_pair(NN, U, V, A, B);
  if (!answered) {
    wrong_answer("answered not exactly once");
  }
  if (wrong_pair) {
    wrong_answer("{s, t} is wrong");
  }
  printf("Accepted: %d\n", num_calls);
  return 0;
}
