#include <iostream>
#include <vector>
#include "dual.cpp"

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);

  int n,v;
  std::vector<int> a,b;
  std::cin >> n >> v;
  a.resize(n); b.resize(n);
  for (int i = 0;i < n;i++) cin >> a[i];
  for (int i = 0;i < n;i++) cin >> b[i];

  long long res = dual_fuel(n,v,a,b);
  std::cout << res << std::endl;
}
