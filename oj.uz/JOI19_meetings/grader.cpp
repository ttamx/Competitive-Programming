#include "meetings.cpp"
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <utility>
#include <vector>

namespace {

const int MAX_N = 2000;
const int MAX_CALLS = 100000;

void WrongAnswer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(0);
}

int N, num_calls;
std::vector<int> graph[MAX_N];
std::set<std::pair<int, int>> edges, edges_reported;

int weight[MAX_N];

bool Visit(int p, int e, int rt = -1) {
  if (p == e) {
    ++weight[p];
    return true;
  }
  for (int q : graph[p]) {
    if (q != rt) {
      if (Visit(q, e, p)) {
        ++weight[p];
        return true;
      }
    }
  }
  return false;
}

}  // namespace

int Query(int u, int v, int w) {
  if (!(0 <= u && u <= N - 1 && 0 <= v && v <= N - 1 && 0 <= w && w <= N - 1 &&
        u != v && u != w && v != w)) {
    WrongAnswer(1);
  }
  if (++num_calls > MAX_CALLS) {
    WrongAnswer(2);
  }
  std::fill(weight, weight + N, 0);
  Visit(u, v);
  Visit(u, w);
  Visit(v, w);
  for (int x = 0; x < N; ++x) {
    if (weight[x] == 3) {
      return x;
    }
  }
  printf("Error: the input may be invalid\n");
  exit(0);
}

void Bridge(int u, int v) {
  if (!(0 <= u && u < v && v <= N - 1)) {
    WrongAnswer(3);
  }
  if (!(edges.count(std::make_pair(u, v)) >= 1)) {
    WrongAnswer(4);
  }
  if (!(edges_reported.count(std::make_pair(u, v)) == 0)) {
    WrongAnswer(5);
  }
  edges_reported.insert(std::make_pair(u, v));
}

int main() {
  if (scanf("%d", &N) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    if (scanf("%d%d", &u, &v) != 2) {
      fprintf(stderr, "Error while reading input\n");
      exit(1);
    }
    graph[u].push_back(v);
    graph[v].push_back(u);
    edges.insert(std::make_pair(u, v));
  }

  num_calls = 0;
  Solve(N);
  if (edges_reported.size() != static_cast<size_t>(N - 1)) {
    WrongAnswer(6);
  }
  printf("Accepted: %d\n", num_calls);
  return 0;
}
