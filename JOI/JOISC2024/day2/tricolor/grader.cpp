#include "Anna.h"
#include "Bruno.h"

namespace {

void wrongAnswer(int code) {
  printf("wrong Answer [%d]\n", code);
  exit(0);
}

const int l_limit = 130;
int N;
std::string S;
int Q;
int a[10000];

}  // namespace

int main(int argc, char **argv) {
  char buf[500001];
  if (scanf("%d", &N) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  if (scanf("%s", buf) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  S = buf;

  auto [t, l] = anna(N, S);

  if ((int)t.size() != N) wrongAnswer(1);

  for (auto c : t) {
    if (!(c == 'R' || c == 'G' || c == 'B')) {
      wrongAnswer(2);
    }
  }

  for (int i = 0; i < N; i++) {
    if (S[i] == t[i]) {
      wrongAnswer(3);
    }
  }

  if (!(l >= 1 && l <= std::min(N, l_limit))) wrongAnswer(4);

  init(N, l);

  if (scanf("%d", &Q) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }

  for (int i = 0; i < Q; i++) {
    if (scanf("%d", &a[i]) != 1) {
      fprintf(stderr, "Error while reading input\n");
      exit(1);
    }
  }

  for (int i = 0; i < Q; i++) {
    std::string u = t.substr(a[i] - 1, l);
    int Answer = bruno(u);
    if (a[i] != Answer) wrongAnswer(5);
  }

  printf("Accepted: %d\n", l);
  return 0;
}
