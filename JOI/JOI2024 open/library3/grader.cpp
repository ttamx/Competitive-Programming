#include "library3.cpp"

#include <cstdio>
#include <cstdlib>
#include <random>
#include <utility>
#include <vector>

namespace {

const int INVALID_A_LENGTH = 1;
const int INVALID_A_RANGE = 2;
const int A_NOT_DIFFERENT = 3;
const int QUERY_LIMIT_EXCEEDED = 4;
const int INVALID_B_LENGTH = 5;
const int INVALID_B_RANGE = 6;
const int B_NOT_DIFFERENT = 7;
const int WRONG_B = 8;
const int ANSWER_TWICE = 9;
const int NO_ANSWER = 10;

const int QUERY_LIMIT = 500000;

int N;
std::vector<int> B;

int query_count = 0;
bool answered = false;

void WrongAnswer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(0);
}

}  // namespace

int query(std::vector<int> a) {
  if (int(a.size()) != N) {
    WrongAnswer(INVALID_A_LENGTH);
  }

  for (int i = 0; i < N; i++) {
    if (a[i] < 0 || N - 1 < a[i]) {
      WrongAnswer(INVALID_A_RANGE);
    }
  }

  std::vector<int> flag(N, 0);
  for (int i = 0; i < N; i++) {
    if (flag[a[i]] > 0) {
      WrongAnswer(A_NOT_DIFFERENT);
    }
    flag[a[i]]++;
  }

  query_count++;
  if (query_count > QUERY_LIMIT) {
    WrongAnswer(QUERY_LIMIT_EXCEEDED);
  }
  int ret = 0;
  bool correct = false;
  while (!correct) {
    int x = -1, y = -1;
    for (int i = 0; i < N; i++) {
      if (a[i] != B[i]) {
        x = i;
        for (int j = 0; j < N; j++) {
          if (a[i] == B[j]) {
            y = j;
          }
        }
        break;
      }
    }
    if (x == -1) {
      correct = true;
    } else {
      std::swap(a[x], a[y]);
      ret++;
    }
  }
  return ret;
}

void answer(std::vector<int> b) {
  if (answered) {
    WrongAnswer(ANSWER_TWICE);
  }
  answered = true;

  if (int(b.size()) != N) {
    WrongAnswer(INVALID_B_LENGTH);
  }

  for (int i = 0; i < N; i++) {
    if (b[i] < 0 || N - 1 < b[i]) {
      WrongAnswer(INVALID_B_RANGE);
    }
  }

  std::vector<int> flag(N, 0);
  for (int i = 0; i < N; i++) {
    if (flag[b[i]] > 0) {
      WrongAnswer(B_NOT_DIFFERENT);
    }
    flag[b[i]]++;
  }

  for (int i = 0; i < N; i++) {
    if (b[i] != B[i]) {
      WrongAnswer(WRONG_B);
    }
  }
}

int main() {
  N=500;
  // if (scanf("%d", &N) != 1) {
  //   fprintf(stderr, "Error while reading input.\n");
  //   exit(1);
  // }
  B.resize(N);
  iota(B.begin(),B.end(),0);
  shuffle(B.begin(),B.end(),rng);
  // for (int i = 0; i < N; i++) {
  //   if (scanf("%d", &B[i]) != 1) {
  //     fprintf(stderr, "Error while reading input.\n");
  //     exit(1);
  //   }
  // }
  solve(N);
  if (!answered) {
    WrongAnswer(NO_ANSWER);
  }
  printf("Accepted: %d\n", query_count);
  return 0;
}
