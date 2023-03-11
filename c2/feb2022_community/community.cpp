#include "community.h"
#include <bits/stdc++.h>

using namespace std;

template<long long mod>
struct modular{
  long long val;
  modular(long long x=0){ val=x%mod; if(val<0)val+=mod;}
  modular inv();
  modular& operator+=(const modular&o){val=(val+o.val)%mod; return *this;}
  modular& operator-=(const modular&o){val=(val-o.val+mod)%mod; return *this;}
  modular& operator*=(const modular&o){val=(val*o.val)%mod; return *this;}
  modular& operator/=(const modular&o){val=(val*o.inv().val)%mod; return *this;}
  friend modular operator+(const modular &lhs,const modular &rhs){return modular(lhs)+=rhs;}
  friend modular operator-(const modular &lhs,const modular &rhs){return modular(lhs)-=rhs;}
  friend modular operator*(const modular &lhs,const modular &rhs){return modular(lhs)*=rhs;}
  friend modular operator/(const modular &lhs,const modular &rhs){return modular(lhs)/=rhs;}
  modular& operator++(){return *this+=1;}
  modular& operator--(){return *this-=1;}
  modular operator++(int){modular ret=*this; *this+=1; return ret;}
  modular operator--(int){modular ret=*this; *this-=1; return ret;}
  bool operator==(const modular &o){return val==o.val;}
  bool operator!=(const modular &o){return val!=o.val;}
  modular binpow(long long pow)const{modular tmp=*this,ret=1; for(;pow;tmp*=tmp,pow>>=1)if(pow&1)ret*=tmp; return ret;}
  modular inv()const{return binpow(mod-2);}
};

const int N=1005;
const int MOD=1e9+7;

typedef modular<MOD> mod;

mod ans,save;
mod cut[N],cnt[N],cutprev[N],line[N],cutwith[N][N];
mod lnk[N][2];
vector<pair<int,int>> v;
bool used[N],usednxt[N];

int minimum_cost(int n, std::vector<int> w){
  if(n>1000)return 0;
  lnk[0][0]=0,lnk[0][1]=0;
  mod add=0;
  cut[0]=0,cnt[0]=6,line[0]=3,cutprev[0]=0;
  for(int i=1;i<n;++i){
    if(i&1)add++;
    cutprev[i]=cutprev[i-1]*4+2;
    if(i&1)cutprev[i]+=2;
    line[i]=line[i-1]*4+3;
    cnt[i]=cnt[i-1]*4+i*6+mod(2).binpow(i+1)*3;
    cut[i]=cut[i-1]*4+lnk[i-1][0]*4+lnk[i-1][1]*2+4*i;
    lnk[i][0]=lnk[i-1][1];
    lnk[i][1]=lnk[i-1][1]+add;
  }
  for(int i=0;i<n;++i){
    ans+=line[i]*w[i]*mod(2).binpow(n-i);
  }
  cout << ans.val << '\n';
  for(int i=1;i<n;++i){
    v.push_back({w[i],i});
  }
  for(int i=n-1;i>=1;--i)cut[i]-=cut[i-1];
  used[n]=true;
  sort(v.rbegin(),v.rend());
  for(auto [x,i]:v){
    if(used[i]&&used[i+1])continue;
    mod cutable=-1;
    if(!used[i])cutable+=cut[i];
    if(!used[i+1])cutable+=cutprev[i+1];
    save+=cutable*x;
    cout << i << ' ' << x << ' ' << cutable.val << '\n';
  }
  ans-=save;
  return ans.val;
}