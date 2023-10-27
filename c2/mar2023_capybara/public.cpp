#include "capybara.cpp"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

int main(){
  int n,q,a,b;
  vector<int>m,k;
  assert(scanf("%d %d",&n,&q)==2);
  for(int i=0;i<n;i++){
    assert(scanf("%d",&a)==1);
    m.push_back(a);
  }
  for(int i=0;i<n-1;i++){
    assert(scanf("%d",&a)==1);
    k.push_back(a);
  }
  capybara(n,q,m,k);
  for(int i=0;i<q;i++){
      assert(scanf("%d %d",&a,&b)==2);
      printf("%lld\n",travel(a,b));
  }
}
