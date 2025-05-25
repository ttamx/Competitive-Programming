#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "circuit.cpp"

namespace {

enum {
  INVALID_T_LENGTH = 1,
  INVALID_T_CHAR = 2,
  WRONG_T = 3,
  INVALID_S_LENGTH = 4,
  INVALID_S_CHAR = 5,
  QUERY_LIMIT_EXCEEDED = 6,
};

const int QUERY_LIMIT = 1000;
int QUERY_COUNT = 0;

void wrong_answer(int code) {
  std::cout << "Wrong Answer [" << code << "]\n";
  exit(1);
}

int get() {
  int x;
  std::cin >> x;
  if (std::cin.fail()) {
    std::cerr << "Error while reading input.\n";
    exit(1);
  }
  return x;
}

int N, R;
std::vector<int> U, V;
std::string T;

}  // namespace

int query(std::string s) {
  const int M = N * 2 + 1;
  if ((int)s.size() != M) {
    wrong_answer(INVALID_S_LENGTH);
  }
  for (char c : s) {
    if (c != '0' && c != '1') {
      wrong_answer(INVALID_S_CHAR);
    }
  }
  if (QUERY_COUNT == QUERY_LIMIT) {
    wrong_answer(QUERY_LIMIT_EXCEEDED);
  }
  QUERY_COUNT++;

  for (char& c : s) c -= '0';
  for (int i = N - 1; i >= 0; i--) {
    const int u = U[i], v = V[i];
    if (T[i] == '&') {
      s[i] ^= s[u] & s[v];
    } else {
      s[i] ^= s[u] | s[v];
    }
  }

  return s[0];
}

int main() {
  N = get();
  R = get();
  
  if (N <= 0) {
    std::cerr << "Error while reading input: invalid value of N: " << N
    << std::endl;
    exit(1);
  }
  
  U.resize(N);
  V.resize(N);

  const int M = N * 2 + 1;
  std::vector<bool> out_edge(M);
  for (int i = 0; i < N; i++) {
    U[i] = get();
    V[i] = get();
    const int u = U[i], v = V[i];

    if (!(i < u && u <= N * 2)) {
      std::cerr << "Error while reading input: invalid value of U[" << i
                << "]: " << u << std::endl;
      exit(1);
    }
    if (!(i < v && v <= N * 2)) {
      std::cerr << "Error while reading input: invalid value of V[" << i
                << "]: " << v << std::endl;
      exit(1);
    }
    if (out_edge[u]) {
      std::cerr << "Error while reading input: multiple connection from " << u
                << std::endl;
      exit(1);
    }
    out_edge[u] = true;
    if (out_edge[v]) {
      std::cerr << "Error while reading input: multiple connection from " << v
                << std::endl;
      exit(1);
    }
    out_edge[v] = true;
  }

  std::cin >> T;
  if ((int)T.size() != N) {
    std::cerr << "Error while reading input: invalid length of t\n";
    exit(1);
  }
  for (char c : T) {
    if (c != '&' && c != '|') {
      std::cerr << "Error while reading input: invalid character in t\n";
      exit(1);
    }
  }

  std::string answer = solve(N, R, U, V);

  if ((int)answer.size() != N) {
    wrong_answer(INVALID_T_LENGTH);
  }
  for (char c : answer) {
    if (c != '&' && c != '|') {
      wrong_answer(INVALID_T_CHAR);
    }
  }
  if (answer != T) {
    wrong_answer(WRONG_T);
  }

  std::cout << "Accepted: " << QUERY_COUNT << "\n";
  return 0;
}
