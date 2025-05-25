#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include "combo.h"
#include "combo.cpp"

namespace {

constexpr int MAX_N = 2000;
constexpr int MAX_NUM_MOVES = 8000;

int N;
std::string S;

int num_moves;

void wrong_answer(const char *MSG) {
  printf("Wrong Answer: %s\n", MSG);
  exit(0);
}

}  // namespace

int press(std::string p) {

  cerr << "PRESS : "  << p << "\n";

  if (++num_moves > MAX_NUM_MOVES) {
    wrong_answer("too many moves");
  }
  int len = p.length();
  if (len > 4 * N) {
    wrong_answer("invalid press");
  }
  for (int i = 0; i < len; ++i) {
    if (p[i] != 'A' && p[i] != 'B' && p[i] != 'X' && p[i] != 'Y') {
      wrong_answer("invalid press");
    }
  }
  int coins = 0;
  for (int i = 0, j = 0; i < len; ++i) {
    if (j < N && S[j] == p[i]) {
      ++j;
    } else if (S[0] == p[i]) {
      j = 1;
    } else {
      j = 0;
    }
    coins = std::max(coins, j);
  }
  return coins;
}

int main() {
  char buffer[MAX_N + 1];
  if (scanf("%s", buffer) != 1) {
    fprintf(stderr, "Error while reading input\n");
    exit(1);
  }
  S = buffer;
  N = S.length();

  num_moves = 0;
  std::string answer = guess_sequence(N);

  std::cerr << "ANSWER : " << answer << "\n";

  if (answer != S) {
    wrong_answer("wrong guess");
    exit(0);
  }
  printf("Accepted: %d\n", num_moves);
  return 0;
}
