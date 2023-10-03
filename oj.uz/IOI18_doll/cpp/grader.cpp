#include <cstdio>
#include <cstdlib>
#include "doll.cpp"

namespace {

constexpr int P_MAX = 20000000;
constexpr int S_MAX = 400000;

int M, N;
std::vector<int> A;

bool answered;
int S;
std::vector<int> IC, IX, IY;

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

void simulate() {
  if (S > S_MAX) {
    char str[50];
    sprintf(str, "over %d switches", S_MAX);
    wrong_answer(str);
  }
  for (int i = 0; i <= M; ++i) {
    if (!(-S <= IC[i] && IC[i] <= M)) {
      wrong_answer("wrong serial number");
    }
  }
  for (int j = 1; j <= S; ++j) {
    if (!(-S <= IX[j - 1] && IX[j - 1] <= M)) {
      wrong_answer("wrong serial number");
    }
    if (!(-S <= IY[j - 1] && IY[j - 1] <= M)) {
      wrong_answer("wrong serial number");
    }
  }

  int P = 0;
  std::vector<bool> state(S + 1, false);
  int pos = IC[0];
  int k = 0;
  FILE *file_log = fopen("log.txt", "w");
  fprintf(file_log, "0\n");
  for (;;) {
    fprintf(file_log, "%d\n", pos);
    if (pos < 0) {
      if (++P > P_MAX) {
        fclose(file_log);
        char str[50];
        sprintf(str, "over %d inversions", P_MAX);
        wrong_answer(str);
      }
      state[-pos] = !state[-pos];
      pos = state[-pos] ? IX[-(1 + pos)] : IY[-(1 + pos)];
    } else {
      if (pos == 0) {
        break;
      }
      if (k >= N) {
        fclose(file_log);
        wrong_answer("wrong motion");
      }
      if (pos != A[k++]) {
        fclose(file_log);
        wrong_answer("wrong motion");
      }
      pos = IC[pos];
    }
  }
  fclose(file_log);
  if (k != N) {
    wrong_answer("wrong motion");
  }
  for (int j = 1; j <= S; ++j) {
    if (state[j]) {
      wrong_answer("state 'Y'");
    }
  }
  printf("Accepted: %d %d\n", S, P);
}

}  // namespace

void answer(std::vector<int> C, std::vector<int> X, std::vector<int> Y) {
  cerr << "C :";
  for(auto x:C)cerr << " " << x;
  cerr << "\n";
  cerr << "X :";
  for(auto x:X)cerr << " " << x;
  cerr << "\n";
  cerr << "Y :";
  for(auto x:Y)cerr << " " << x;
  cerr << "\n";
  if (answered) {
    wrong_answer("answered not exactly once");
  }
  answered = true;
  // check if input format is correct
  if ((int)C.size() != M + 1) {
    wrong_answer("wrong array length");
  }
  if (X.size() != Y.size()) {
    wrong_answer("wrong array length");
  }
  S = X.size();
  IC = C;
  IX = X;
  IY = Y;
}

int main() {
  M = read_int();
  N = read_int();
  A.resize(N);
  for (int k = 0; k < N; ++k) {
    A[k] = read_int();
  }

  answered = false;
  create_circuit(M, A);
  if (!answered) {
    wrong_answer("answered not exactly once");
  }
  FILE *file_out = fopen("out.txt", "w");
  fprintf(file_out, "%d\n", S);
  for (int i = 0; i <= M; ++i) {
    fprintf(file_out, "%d\n", IC[i]);
  }
  for (int j = 1; j <= S; ++j) {
    fprintf(file_out, "%d %d\n", IX[j - 1], IY[j - 1]);
  }
  fclose(file_out);
  simulate();
  return 0;
}
