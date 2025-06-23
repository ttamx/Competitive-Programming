#include "starter.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=80005;
const int K=1<<18;
const ll INF=1e18;

int n;
ll c[N];
vector<int> adj[N];
int tin[N],tout[N];
int timer;

ll fdiv(ll a,ll b){
	return a/b-((a^b)<0&&a%b);
}

struct Segtree{
	set<ll> s[K];
	void update(int l,int r,int i,int x,ll v){
		s[i].emplace(v);
		if(l==r)return;
		int m=(l+r)/2;
		if(x<=m)update(l,m,i*2,x,v);
		else update(m+1,r,i*2+1,x,v);
	}
	void update(int x,ll v){
		update(1,n,1,x,v);
	}
	ll query(int l,int r,int i,int x,int y,ll v,ll k){
		if(y<l||r<x)return INF;
		if(x<=l&&r<=y){
			ll res=INF;
			auto it=s[i].upper_bound(fdiv(v,k));
			if(it!=s[i].end())res=min(res,abs(*it*k-v));
			if(it!=s[i].begin())res=min(res,abs(*prev(it)*k-v));
			return res;
		}
		int m=(l+r)/2;
		return min(query(l,m,i*2,x,y,v,k),query(m+1,r,i*2+1,x,y,v,k));
	}
	ll query(int x,int y,ll v,ll k){
		return query(1,n,1,x,y,v,k);
	}
}seg;

ll dfs(int u,int p){
	tin[u]=++timer;
	for(auto v:adj[u])if(v!=p)c[u]+=dfs(v,u);
	tout[u]=timer;
	seg.update(tin[u],c[u]);
	return c[u];
}

void initialize(int _n,int _q,vector<int> _u,vector<int> _v,vector<int> _a){
	n=_n;
	for(int i=0;i<n;i++)c[i]=_a[i];
	for(int i=0;i<n-1;i++){
		int u=_u[i],v=_v[i];
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	dfs(0,-1);
}

ll answer(int x,ll a,ll b){
	return min(seg.query(tin[x],tout[x],a*c[x],a+b),seg.query(tin[x],tout[x],b*c[x],a+b));
}