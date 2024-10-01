#include "Anna.h"
#include <bits/stdc++.h>

using namespace std;

void Anna(int n,vector<char> s){
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
  dp[1][0]=1;
  dp[1][1]=1;
  for(int i=2;i<=F;i++){
    dp[i][0]=add(dp[i-1][0],dp[i-1][1]);
    dp[i][1]=dp[i-1][0];
  }
  int st=-1;
  for(int i=0;i<n;i++){
    if(s[i]=='X'){
      st=i;
      break;
    }
  }
  if(st==-1){
    Send(0);
    return;
  }
  for(int i=0;i<17;i++){
    Send(st>>i&1);
  }
  int sz=((n-1)/F+1)*F;
  vector<int> seq(sz);
  for(int i=st+1;i<n;i++){
    if(s[i]=='Z'&&(i==n-1||s[i+1]!='Z')){
      seq[i]=1;
    }
  }
  for(int i=0;i<sz;i+=F){
    BS res;
    for(int j=0;j<F;j++){
      if(seq[i+j]){
        res=add(res,dp[F-j][0]);
      }
    }
    for(int j=0;j<B;j++){
      Send(res[j]);
    }
  }
}