#include <iostream>
#include <vector>
#include "mazes.cpp"

using namespace std;
using ll = long long;
const int N = 200, M = 200;

vector<vector<char>> solve(ll K);

int main() {
  ios_base::sync_with_stdio(false);
  ll K;

  cin >> K;

  vector<vector<char>> ans = solve(K);
  int n = ans.size();
  int m = (n != 0) ? ans[0].size() : 0;

  cout << n << ' ' << m << '\n';
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << ans[i][j];
    }
    cout << '\n';
  }

  return 0;
}
