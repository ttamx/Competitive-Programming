#include "lingling.h"
#include <vector>
#include <cstdio>
#include "lingling.cpp"

int main(){
  int n;
  scanf("%d",&n);
  std::vector<int> P;
  P.reserve(n);
  int x;
  for(int i = 0; i < n; i++){
    scanf("%d", &x);
    P.push_back(x);
  }
  int Q;
  scanf("%d",&Q);
  init_monkeys(P, Q);
  for(int i = 0; i < Q; i++){
    int l, r;
    scanf("%d%d",&l,&r);
    long long output = minimum_branches(l, r);
    printf("%lld\n",output);
  }
  return 0;
}