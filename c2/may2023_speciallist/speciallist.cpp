#include "speciallist.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
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

int n,m;
vector<int> adj[N];
vector<int> ans;
vector<int> X;
mint cur;
int sz[N],hv[N],pos[N],tin[N],tout[N];
int t;

struct fenwick{
	mint t[N];
	void add(int i,mint v){
		i++;
		while(i<N)t[i]+=v,i+=i&-i;
	}
	mint read(int i){
		i++;
		mint res=0;
		while(i>0)res+=t[i],i-=i&-i;
		return res;
	}
}f,f2;

mint pw2(mint x){
	return x*x;
}

void add(int x,int t){
	mint l=f.read(x-1);
	mint l2=f2.read(x-1);
	mint r=f.read(N-2)-f.read(x);
	mint r2=f2.read(N-2)-f2.read(x);
	cur+=t*(l*pw2(x)-l2+r2-r*pw2(x));
	f.add(x,t);
	f2.add(x,t*pw2(x));
}

void predfs(int u){
	hv[u]=-1;
	tin[u]=++t;
	pos[t]=u;
	sz[u]=1;
	for(auto v:adj[u]){
		predfs(v);
		sz[u]+=sz[v];
		if(hv[u]==-1||sz[v]>sz[hv[u]])hv[u]=v;
	}
	tout[u]=t;
}

void dfs(int u,bool del=true){
	for(auto v:adj[u])if(v!=hv[u])dfs(v);
	if(hv[u]!=-1)dfs(hv[u],false);
	add(X[u],1);
	for(auto v:adj[u])if(v!=hv[u])for(int i=tin[v];i<=tout[v];i++)add(X[pos[i]],1);
	ans[u]=cur.x;
	if(del)for(int i=tin[u];i<=tout[u];i++)add(X[pos[i]],-1);
}

vector<int> compute_cost(int N,int M,vector<int> P,vector<int> _X,vector<int> Z){
	n=N,m=M,X=_X;
	ans.resize(n);
	for(int i=1;i<n;i++)adj[P[i]].emplace_back(i);
	for(auto x:Z)add(x,1);
	predfs(0);
	dfs(0);
	return ans;
}