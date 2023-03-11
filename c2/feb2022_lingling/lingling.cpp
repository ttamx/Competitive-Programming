#include "lingling.h"
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=2e5+5;
const int K=1<<19;

struct fenwick{
  long long f[N];
  void clear(){
    for(int i=0;i<N;++i)f[i]=0;
  }
  void add(int i,long long v){
    while(i<N)f[i]+=v,i+=i&-i;
  }
  long long read(int i){
    long long ret=0;
    while(i)ret+=f[i],i-=i&-i;
    return ret;
  }
}dis,f;

int n;
int mnr[N];
int pos[N];
long long ans;
bool can=true;

void init_monkeys(std::vector<int> P, int Q){
  n = P.size();
  for(int i=0;i<n;++i){
    pos[P[i]+1]=i+1;
    dis.add(i+1,P[i]-i);
  }
}

long long minimum_branches(int L, int R){
  L++,R++;
  if(dis.read(R)-dis.read(L-1))return -1;
  return 0;
}