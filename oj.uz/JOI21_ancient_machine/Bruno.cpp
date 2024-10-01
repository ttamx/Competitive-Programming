#include "Bruno.h"
#include <bits/stdc++.h>

using namespace std;

void Bruno(int n,int m,vector<int> seq){
  if(m==1){
    for(int i=0;i<n;i++){
      Remove(i);
    }
    return;
  }
  const int B=349;
  const int F=500;
  using BS = bitset<B>;
  vector<array<BS,2>> dp(F+1);
  auto add=[&](const BS &a,const BS &b){
    BS res;
    bool carry=0;
    for(int i=0;i<B;i++){
      res[i]=a[i]^b[i]^carry;
      carry=(a[i]&b[i])|((a[i]^b[i])&carry);
    }
    return res;
  };
  auto sub=[&](const BS &a,const BS &b){
    BS res;
    int borrow=0;
    for(int i=0;i<B;i++){
      int x=int(a[i])-b[i];
      x-=borrow;
      if(x<0){
        x+=2;
        borrow=1;
      }else{
        borrow=0;
      }
      res[i]=x;
    }
    return res;
  };
  auto lesseq=[&](const BS &a,const BS &b){
    for(int i=B-1;i>=0;i--){
      if(a[i]<b[i])return true;
      if(a[i]>b[i])return false;
    }
    return true;
  };
  dp[1][0]=1;
  dp[1][1]=1;
  for(int i=2;i<=F;i++){
    dp[i][0]=add(dp[i-1][0],dp[i-1][1]);
    dp[i][1]=dp[i-1][0];
  }
  int p=0;
  for(int i=0;i<17;i++){
    p|=seq[i]<<i;
  }
  vector<int> a;
  for(int i=17;i<m;i+=B){
    BS res;
    for(int j=0;j<B;j++){
      res[j]=seq[i+j];
    }
    for(int j=0;j<F;j++){
      if(lesseq(dp[F-j][0],res)){
        res=sub(res,dp[F-j][0]);
        a.emplace_back(1);
      }else{
        a.emplace_back(0);
      }
    }
  }
  for(int i=0;i<p;i++){
    Remove(i);
  }
  stack<int> s;
  for(int i=p+1;i<n;i++){
    if(a[i]){
      while(!s.empty()){
        Remove(s.top());
        s.pop();
      }
      Remove(i);
    }else{
      s.emplace(i);
    }
  }
  while(!s.empty()){
    Remove(s.top());
    s.pop();
  }
  Remove(p);
}
