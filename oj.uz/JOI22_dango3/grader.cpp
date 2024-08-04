#include <cstdio>
#include <cstdlib>

#include "dango3.cpp"

namespace {

using std::exit;
using std::fprintf;
using std::printf;
using std::scanf;

constexpr int Q_MAX = 50'000;
constexpr int NM_MAX = 10'000;

int N;
int M;
int C[NM_MAX + 1];

int query_count = 0;
int answer_count = 0;
bool finishes[NM_MAX + 1];

void WrongAnswer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(0);
}
}  // namespace

int Query(const std::vector<int> &x) {
  if (++query_count > Q_MAX) WrongAnswer(3);
  bool presents[NM_MAX + 1];
  for (int i = 1; i <= N * M; ++i) presents[i] = false;
  int colors[NM_MAX + 1];
  for (int i = 1; i <= N; i++) colors[i] = 0;
  for (const int t : x) {
    if (t <= 0 || t > N * M) WrongAnswer(1);
    if (presents[t]) WrongAnswer(2);
    presents[t] = true;
    colors[C[t]]++;
  }
  int color_min = M;
  for (int i = 1; i <= N; i++) {
    if (colors[i] < color_min) color_min = colors[i];
  }
  return color_min;
}

void Answer(const std::vector<int> &a) {
  ++answer_count;
  if ((int)a.size() != N) WrongAnswer(4);
  for (const int t : a) {
    if (t <= 0 || t > N * M) WrongAnswer(5);
    if (finishes[t]) WrongAnswer(6);
    finishes[t] = true;
  }
  int colors[NM_MAX + 1];
  for (int i = 1; i <= N; i++) colors[i] = 0;
  for (const int t : a) {
    colors[C[t]]++;
  }
  for (int i = 1; i <= N; i++) {
    if (colors[i] != 1) WrongAnswer(7);
  }
}

int main() {
  if (scanf("%d%d", &N, &M) != 2) {
    fprintf(stderr, "Error while reading input.\n");
    exit(1);
  }
  for (int i = 1; i <= N * M; ++i) {
    if (scanf("%d", &C[i]) != 1) {
      fprintf(stderr, "Error while reading input.\n");
      exit(1);
    }
  }
  for (int i = 1; i <= N * M; ++i) finishes[i] = false;
  Solve(N, M);
  if (answer_count != M) WrongAnswer(8);
  printf("Accepted: %d\n", query_count);
  return 0;
}
