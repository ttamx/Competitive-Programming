#include "community.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const ll mod=1e9+7;

struct mint{
	ll x;
	mint(ll x=0):x(x%mod){}
	ll norm(ll x){
		if(x<0)x+=mod;
		if(x>=mod)x-=mod;
		return x;
	}
	mint& operator+=(const mint &rhs){x=norm(x+rhs.x);return *this;}
	mint& operator-=(const mint &rhs){x=norm(x-rhs.x);return *this;}
	mint& operator*=(const mint &rhs){x=(x*rhs.x)%mod;return *this;}
	friend mint operator+(const mint &lhs,const mint &rhs){return mint(lhs)+=rhs;}
	friend mint operator-(const mint &lhs,const mint &rhs){return mint(lhs)-=rhs;}
	friend mint operator*(const mint &lhs,const mint &rhs){return mint(lhs)*=rhs;}
};

struct fenwick{
	mint t[N];
	void add(int i,mint v){
		while(i<N)t[i]+=v,i+=i&-i;
	}
	mint read(int i){
		mint res=0;
		while(i>0)res+=t[i],i-=i&-i;
		return res;
	}
}f,f2;

int n;
mint dp[N],pw2[N],cnt[N],pcut[N],ncut[N];

int minimum_cost(int n, vector<int> w){
	mint ans;
	pw2[0]=1;
	for(int i=1;i<=n;i++)pw2[i]=pw2[i-1]*2;
	for(int i=1;i<=n;i++){
		dp[i]=4*dp[i-1]+(i%2==0?2:4);
		cnt[i]=4*cnt[i-1]+3;
		ans+=cnt[i]*w[i-1]*pw2[n-i+1];
		pcut[i]=pcut[i-1]+dp[i-1];
		ncut[i]=dp[i]*(n-i);
	}
	vector<pair<int,int>> vec;
	for(int i=1;i<=n;i++)vec.emplace_back(w[i-1],i);
	sort(vec.rbegin(),vec.rend());
	int cnt=0;
	for(auto [x,i]:vec){
		if(++cnt==n)break;
		ans-=(pcut[i]+ncut[i]-dp[i]*f.read(i)-f2.read(i)-1)*x;
		f.add(1,1);
		f.add(i,-1);
		f2.add(i+1,dp[i]);
	}
	return ans.x;
}