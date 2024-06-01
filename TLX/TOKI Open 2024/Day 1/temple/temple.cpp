#include "temple.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3e5+5;
const int K=1<<18;
const ll INF=LLONG_MAX/2;

int n,m;
int p[N],l[N],r[N];
map<int,vector<pair<int,int>>> edge;
vector<int> adj[N],adj2[N];
vector<int> comp,ch[N];
bool vis[N];
int node_id;
vector<tuple<int,int,vector<int>>> opr;
int timer=0;

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
	void update(int l,int r,int i,int x,int y,ll v){
		if(y<l||r<x)return;
		if(x<=l&&r<=y)return void(t[i]=min(t[i],v));
		int m=(l+r)/2;
		update(l,m,i*2,x,y,v);
		update(m+1,r,i*2+1,x,y,v);
	}
	void update(int x,int y,ll v){
		update(1,n,1,x,y,v);
	}
	ll query(int l,int r,int i,int x){
		if(l==r)return t[i];
		int m=(l+r)/2;
		return min(t[i],x<=m?query(l,m,i*2,x):query(m+1,r,i*2+1,x));
	}
	ll query(int x){
		return query(1,n,1,x);
	}
}s;

int fp(int u){
	return p[u]=u==p[u]?u:fp(p[u]);
}

void dfs(int u){
	vis[u]=true;
	comp.emplace_back(u);
	for(auto v:adj[u])if(!vis[v])dfs(v);
}

void dfs2(int u){
	if(u<n)return void(l[u]=r[u]=++timer);
	l[u]=n;
	for(auto v:adj2[u]){
		dfs2(v);
		l[u]=min(l[u],l[v]);
		r[u]=max(r[u],r[v]);
	}
}

ll min_weight(int _n,int _m,int _k,vector<int> U,vector<int> V,vector<int> W,vector<int> P){
	n=_n,m=_m;
	node_id=n;
	for(int i=0;i<n;i++)p[i]=i;
	for(int i=0;i<m;i++)edge[W[i]].emplace_back(U[i],V[i]);
	for(auto &[w,e]:edge){
		vector<int> nodes;
		for(auto [u,v]:e){
			int pu=fp(u),pv=fp(v);
			nodes.emplace_back(pu);
			nodes.emplace_back(pv);
			adj[pu].emplace_back(pv);
			adj[pv].emplace_back(pu);
			ch[pu].emplace_back(u);
			ch[pv].emplace_back(v);
		}
		for(auto x:nodes)if(!vis[x]){
			dfs(x);
			ll res=INF;
			int rt=node_id++;
			p[rt]=rt;
			for(auto u:comp){
				u=fp(u);
				if(u!=rt){
					p[u]=rt;
					adj2[rt].emplace_back(u);
				}
			}
			opr.emplace_back(w,rt,comp);
			comp.clear();
		}
		for(auto x:nodes){
			adj[x].clear();
			vis[x]=false;
		}
	}
	dfs2(node_id-1);
	s.build();
	for(auto x:P)s.update(l[x],l[x],0LL);
	for(auto &[w,rt,comp]:opr){
		ll res=INF;
		for(auto u:comp)for(auto x:ch[u])res=min(res,s.query(l[x]));
		s.update(l[rt],r[rt],res+w);
	}
	return s.query(l[0]);
}
