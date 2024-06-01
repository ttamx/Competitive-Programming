#include"orgdelivery.h"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;
const ll INF =LLONG_MAX/2;

int n,q;
vector<int> adj[N];
int sz[N],hv[N],tin[N],tout[N],pos[N];
int timer;
vector<pair<int,int>> qr[N];
vector<ll> ans;
pair<int,int> val[N];
int a[N];
ll d[N];

struct SegTree{
	ll t[K];
	void build(int l,int r,int i){
		t[i]=INF;
		if(l==r)return;
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
	}
	void build(){
		build(1,n,1);
	}
	void update(int l,int r,int i,int x,ll v){
		if(x<l||r<x)return;
		if(l==r)return void(t[i]=v);
		int m=(l+r)/2;
		update(l,m,i*2,x,v);
		update(m+1,r,i*2+1,x,v);
		t[i]=min(t[i*2],t[i*2+1]);
	}
	void update(int x,ll v){
		update(1,n,1,x,v);
	}
	ll query(int l,int r,int i,int x,int y){
		if(y<l||r<x)return INF;
		if(x<=l&&r<=y)return t[i];
		int m=(l+r)/2;
		return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
	}
	ll query(int x,int y){
		return query(1,n,1,x,y);
	}
}sl,sr;

void dfs(int u){
	sz[u]=1;
	tin[u]=++timer;
	pos[timer]=u;
	for(auto v:adj[u]){
		d[v]+=d[u];
		dfs(v);
		sz[u]+=sz[v];
		if(sz[v]>sz[hv[u]])hv[u]=v;
	}
	tout[u]=timer;
}

void sack(int u,bool del){
	for(auto v:adj[u])if(v!=hv[u])sack(v,true);
	if(hv[u])sack(hv[u],false);
	for(auto v:adj[u])if(v!=hv[u])for(int i=tin[v];i<=tout[v];i++){
		int w=pos[i];
		sl.update(a[w],d[w]-val[a[w]].first);
		sr.update(a[w],d[w]+val[a[w]].first);
	}
	sl.update(a[u],d[u]-val[a[u]].first);
	sr.update(a[u],d[u]+val[a[u]].first);
	for(auto [x,i]:qr[u])ans[i]=min(sl.query(1,a[x])+val[a[x]].first,sr.query(a[x],n)-val[a[x]].first)-d[u];
	if(del)for(int i=tin[u];i<=tout[u];i++){
		int w=pos[i];
		sl.update(a[w],INF);
		sr.update(a[w],INF);
	}
};

vector<ll> mincost(int _n,vector<int> P,vector<ll> V,vector<int> W,int _q,vector<int> A,vector<int> B){
	n=_n,q=_q;
	ans.resize(q);
	for(int i=1;i<n;i++)adj[P[i]+1].emplace_back(i+1);
	for(int i=0;i<q;i++)qr[B[i]+1].emplace_back(A[i]+1,i);
	for(int i=1;i<=n;i++)val[i]={V[i-1],i};
	for(int i=1;i<=n;i++)d[i]=W[i-1];
	sort(val+1,val+n+1);
	for(int i=1;i<=n;i++)a[val[i].second]=i;
	sl.build();
	sr.build();
	dfs(1);
	sack(1,false);
	return ans;
}
