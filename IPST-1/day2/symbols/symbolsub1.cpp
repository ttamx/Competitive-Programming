#include "symbols.h"
#include<bits/stdc++.h>

using namespace std;
// edit this file as you like

typedef long long ll;

const int N=2e5+5;
const int K=1<<19;
const ll mod=20232566;

ll binpow(ll a,ll b){
  ll ret=1;
  while(b){
    if(b&1)ret=(ret*a)%mod;
    a=(a*a)%mod;
    b/=2;
  }
  return ret;
}

int n,q;
ll poww[N],P[30][30];
ll ans,sz;
bool used[N];

void explore_site(int N, int Q) {
    n = N;
    q = Q;
  poww[0]=1;
    for(int i=1;i<=n;i++){
      poww[i]=(poww[i-1]*26)%mod;
    }
    for(int i=0;i<=26;i++){
      P[i][0]=1;
      for(int j=1;j<=i;j++){
        P[i][j]=(P[i][j-1]*(i-j+1))%mod;
      }
    }
    ans=1;
    sz=n;
}

int retrieve_notes(int L, int R) {
  if(!used[L]){
    used[L]=true;
    sz-=1;
    ans=(ans*25)%mod;
  }
  int ret=(ans*poww[sz])%mod;
  return ret;
}