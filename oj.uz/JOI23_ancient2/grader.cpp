#include <cstdio>
#include <cstdlib>

#include "ancient2.cpp"

namespace {

using std::exit;
using std::fprintf;
using std::printf;
using std::scanf;

constexpr int N_MAX = 1'000;
constexpr int M_MAX = 1'002;
constexpr int Q_MAX = 1'000;

int N;
char S[N_MAX + 1];

int query_count = 0;
int query_m_max = 0;

void WrongAnswer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(0);
}
}  // namespace

int Query(int m, std::vector<int> a, std::vector<int> b) {
  if (++query_count > Q_MAX) WrongAnswer(7);
  if (!(1 <= m && m <= M_MAX)) WrongAnswer(4);
  if ((int)a.size() != m || (int)b.size() != m) WrongAnswer(5);
  for (int i = 0; i < m; i++) {
    if (!(0 <= a[i] && a[i] <= m - 1) || !(0 <= b[i] && b[i] <= m - 1))
      WrongAnswer(6);
  }
  if (m > query_m_max) query_m_max = m;
  int memory = 0;
  for (int i = 0; i < N; i++) {
    if (S[i] == '0') {
      memory = a[memory];
    }
    if (S[i] == '1') {
      memory = b[memory];
    }
  }
  return memory;
}

int main() {
  if (scanf("%d", &N) != 1) {
    fprintf(stderr, "Error while reading input.\n");
    exit(1);
  }
  if (scanf("%s", S) != 1) {
    fprintf(stderr, "Error while reading input.\n");
    exit(1);
  }
  std::string s = Solve(N);
  if ((int)s.size() != N) WrongAnswer(1);
  for (int i = 0; i < N; i++) {
    if (!(s[i] == '0' || s[i] == '1')) WrongAnswer(2);
  }
  for (int i = 0; i < N; i++) {
    if (s[i] != S[i]) WrongAnswer(3);
  }
  printf("Accepted: %d\n", query_m_max);
  return 0;
}
