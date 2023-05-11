#include "goatlang.h"
#include "goatlang.cpp"
#include <functional>
#include <iostream>
#include <string>
using namespace std;

vector<vector<int>> id(int n) {
  vector<vector<int>> ret;
  for (int i = 0; i < n; i++) {
    vector<int> row;
    row.resize(n, 0);
    row[i] = 1;
    ret.push_back(row);
  }
  return ret;
}
bool sanitize(vector<vector<int>> &A, int in, int out) {
  int n = A.size();
  if (n > 40)
    return false;
  if (in < 0 || in >= n)
    return false;
  if (out < 0 || out >= n)
    return false;
  for (int i = 0; i < n; i++) {
    if (A[i].size() != n)
      return false;
    for (int j = 0; j < n; j++) {
      if (A[i][j] < 0)
        return false;
      A[i][j] %= 1000000007;
    }
  }
  return true;
}
vector<vector<int>> matmul(vector<vector<int>> A, vector<vector<int>> B) {
  vector<vector<int>> prod = A;
  int n = A.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      prod[i][j] = 0;
      for (int k = 0; k < n; k++) {
        prod[i][j] += 1ll * A[i][k] * B[k][j] % 1000000007;
        prod[i][j] %= 1000000007;
      }
    }
  }
  return prod;
}
int main() {
  string task;
  cin >> task;
  function<tuple<vector<vector<int>>, int, int>()> f;
  int lim = 100;
  if (task == "example1") {
    f = example1;
  } else if (task == "example2") {
    f = example2;
  } else if (task == "task1" || task == "task2") {
    int N, r, c;
    cin >> N >> r >> c;
    vector<vector<int>> A;
    for (int i = 0; i < N; i++) {
      vector<int> row;
      row.reserve(N);
      for (int j = 0; j < N; j++) {
        int x;
        cin >> x;
        row.push_back(x);
      }
      A.push_back(row);
    }
    auto inner = task == "task1" ? task1 : task2;
    f = [A, r, c, inner]() { return inner(A, r, c); };
  } else if (task == "task3") {
    int D;
    cin >> D;
    vector<int> coeffs;
    coeffs.reserve(D + 1);
    for (int i = 0; i <= D; i++) {
      int x;
      cin >> x;
      coeffs.push_back(x);
    }
    f = [coeffs]() { return task3(coeffs); };
  } else if (task == "task4") {
    f = task4;
  } else if (task == "task5") {
    string bs;
    cin >> bs;
    vector<int> bsinp;
    bsinp.reserve(bs.size());
    lim = bs.size();
    for (int i = 0; i < bs.size(); i++)
      bsinp.push_back(bs[i] == '1' ? 1 : 0);
    f = [bsinp]() { return task5(bsinp); };
  } else if (task == "task6") {
    int m;
    cin >> m;
    f = [m]() { return task6(m); };
  } else {
    cerr << "Unknown task. Exiting." << endl;
    exit(1);
  }
  auto prog = f();
  vector<vector<int>> mat, cur;
  int iidx, jidx;
  tie(mat, iidx, jidx) = prog;
  if (!sanitize(mat, iidx, jidx)) {
    cerr << "Invalid return value. Exiting." << endl;
    exit(1);
  }
  cur = id(mat.size());
  for (int n = 1; n <= lim; n++) {
    cur = matmul(cur, mat);
    cout << "n = " << n << " gives " << cur[iidx][jidx] << endl;
  }
  return 0;
}