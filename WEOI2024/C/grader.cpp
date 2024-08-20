#include <iostream>
#include <vector>
#include "multihop.cpp"

using namespace std;

void init(int N, int C, vector<int> A, vector<int> B, vector<int> U,
          vector<int> V);

long long query(int X, int Y);

int main() {
  ios_base::sync_with_stdio(false);
  int N, Q, C;
  cin >> N >> Q >> C;

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  vector<int> B(N);
  for (int i = 0; i < N; i++) {
    cin >> B[i];
  }

  vector<int> U(N - 1), V(N - 1);
  for (int i = 0; i < N - 1; i++) {
    cin >> U[i] >> V[i];
  }

  init(N, C, A, B, U, V);

  for (int i = 0; i < Q; i++) {
    int X, Y;
    cin >> X >> Y;
    cout << query(X, Y) << endl;
  }
  return 0;
}
