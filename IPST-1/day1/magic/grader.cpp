#include "magic.cpp"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

int main(){
  int Q,N,M,a,b,t;
  vector<int>U,V,user_ans;
  vector<vector<int> >q;
  assert(scanf("%d %d %d",&N,&M,&Q)==3);
  for(int i=0;i<M;i++){
    assert(scanf("%d %d",&a,&b)==2);
    U.push_back(a);
    V.push_back(b);
  }
  for(int i=0;i<Q;i++){
    vector<int>query;
    assert(scanf("%d",&t)==1);
    query.push_back(t);
    if(t==0){
      assert(scanf("%d",&a)==1);
      query.push_back(a);
    }
    else{
      assert(scanf("%d %d",&a,&b)==2);
      query.push_back(a);
      query.push_back(b);
    }
    q.push_back(query);
  }
  user_ans = magic(N, M, Q, U, V, q);
  for(int i=0;i<Q;i++){
    if(q[i][0]==1){
      if(user_ans[i]==0)printf("No\n");
      else printf("Yes\n");
    }
  }
}
