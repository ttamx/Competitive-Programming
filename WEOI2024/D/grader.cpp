#include <iostream>
#include <vector>
#include "trees.cpp"

using namespace std;

int count_sets(int N, vector<int> U, vector<int> V);

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int N;
  cin >> N;

  vector<int> U(N - 1), V(N - 1);
  for (int i = 0; i + 1 < N; i++) {
    cin >> U[i] >> V[i];
  }

  int answer = count_sets(N, U, V);
  cout << answer << "\n";

  return 0;
}
