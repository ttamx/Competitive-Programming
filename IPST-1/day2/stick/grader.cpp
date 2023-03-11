#include "stick.cpp"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

int main(){
  int n,q,x,l,r;
  vector<int>X;
  assert(scanf("%d %d",&n,&q)==2);
  for(int i=1;i<=n;i++){
    assert(scanf("%d",&x)==1);
    X.push_back(x);
  }
  init(n,X);
  for(int i=1;i<=q;i++){
    assert(scanf("%d %d",&l,&r)==2);
    printf("%d\n",max_length(l,r));
  }
}
