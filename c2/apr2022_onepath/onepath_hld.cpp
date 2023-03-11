#include "onepath.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

int n,m,q,idx=1;
int p[N],lv[N],pa[N][20],sz[N],mx[N],pos[N],head[N];
vector<int> adj[N];

struct segtree{
	int s[K],lz[K];
	void pushlz(int l,int r,int i){
		if(lz[i]!=1)return;
		if(l<r)lz[i<<1]=lz[i<<1|1]=lz[i];
		s[i]=lz[i];
		lz[i]=2;
	}
	void update(int l,int r,int i,int x,int y){
		pushlz(l,r,i);
		if(r<x||y<l)return;
		if(x<=l&&r<=y){
			if(lz[i]==2)return;
			lz[i]=1;
			pushlz(l,r,i);
			return;
		}
		int m=(l+r)>>1;
		update(l,m,i<<1,x,y);
		update(m+1,r,i<<1|1,x,y);
		s[i]=s[i<<1]|s[i<<1|1];
	}
	void update(int x,int y){
		update(1,n,1,x,y);
	}
	int query(int l,int r,int i,int x,int y){
		pushlz(l,r,i);
		if(r<x||y<l)return 0;
		if(x<=l&&r<=y)return s[i];
		int m=(l+r)>>1;
		if(query(l,m,i<<1,x,y))return 1;
		return query(m+1,r,i<<1|1,x,y);
	}
	int query(int x,int y){
		return query(1,n,1,x,y);
	}
}seg;

int fp(int u){
	if(p[u]==u)return u;
	return p[u]=fp(p[u]);
}

void dfs(int u,int p){
	lv[u]=lv[p]+1;
	pa[u][0]=p;
	for(int i=1;i<=17;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
	sz[u]=1;
	int tmp=0;
	mx[u]=-1;
	for(auto v:adj[u]){
		if(v==p)continue;
		dfs(v,u);
		sz[u]+=sz[v];
		if(sz[v]>tmp){
			tmp=sz[v];
			mx[u]=v;
		}
	}
}

void hld(int u,int p){
	pos[u]=idx++;
	if(mx[u]!=-1){
		head[mx[u]]=head[u];
		hld(mx[u],u);
	}
	for(auto v:adj[u]){
		if(v==p||v==mx[u])continue;
		head[v]=v;
		hld(v,u);
	}
}

void updateup(int u,int v){
	while(head[u]!=head[v]){
		seg.update(pos[head[u]],pos[u]);
		u=pa[head[u]][0];
	}
	seg.update(pos[v]+1,pos[u]);
}

int queryup(int u,int v){
	int ret=0;
	while(head[u]!=head[v]){
		ret|=seg.query(pos[head[u]],pos[u]);
		if(ret)return 1;
		u=pa[head[u]][0];
	}
	ret|=seg.query(pos[v]+1,pos[u]);
	return ret;
}

int lca(int a,int b){
	if(lv[a]<lv[b])swap(a,b);
	for(int i=17;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
	if(a==b)return a;
	for(int i=17;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
	return pa[a][0];
}

void initialize(int N, int M, int Q, vector<pair<int,int>> r) {
	n=N,m=M,q=Q;
	queue<pair<int,int>> qu;
	iota(p,p+n,0);
	for(auto [u,v]:r){
		int pu=fp(u),pv=fp(v);
		if(pu!=pv){
			p[pu]=pv;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}else{
			qu.push({u,v});
		}
	}
	dfs(0,0);
	hld(0,0);
	while(!qu.empty()){
		auto [u,v]=qu.front();
		qu.pop();
		int l=lca(u,v);
		updateup(u,l);
		updateup(v,l);
	}
	return;
}

bool is_dangerous(int u, int v) {
	int l=lca(u,v);
	return 1-(queryup(u,l)|queryup(v,l));
}

void build_road(int u, int v) {
	int l=lca(u,v);
	updateup(u,l);
	updateup(v,l);
	return;
}