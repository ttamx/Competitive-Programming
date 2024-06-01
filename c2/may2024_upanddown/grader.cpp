#include "upanddown.cpp"
#include <vector>
#include <cstdio>

using namespace std;

int main()
{
  int n;
  std::vector<int> X;
  int dummy;
  
  dummy = scanf("%d",&n);
  for(int i=0; i<n; i++) {
    int xx;
    dummy = scanf("%d",&xx);
    X.push_back(xx);
  }
  long long res = upanddown(n, X);
  printf("%lld\n", res);
  return 0;
}
