#include "copper.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int M=2e5+5;
const int LG=18;

int n,m;
vector<int> adj[N],pos[N];
int lv[N],pa[N],psz[N],st[N],sz[N],hv[N],hd[N];

struct Path{
	int to;
	ll cnt;
	Path(){}
	Path(int _to,ll _cnt):to(_to),cnt(_cnt){}
	friend Path operator+(const Path &lhs,const Path &rhs){
		return Path(rhs.to,lhs.cnt+rhs.cnt);
	}
}up[M][LG],down[M][LG];

void dfs(int u,int p=-1){
	sz[u]=1;
	hv[u]=-1;
	for(auto v:adj[u])if(v!=p){
		lv[v]=lv[u]+1;
		pa[v]=u;
		dfs(v,u);
		sz[u]+=sz[v];
		if(hv[u]==-1||sz[v]>sz[hv[u]])hv[u]=v;
	}
}

void hld(int u,int p=-1){
	if(hv[u]!=-1)hd[hv[u]]=hd[u],hld(hv[u],u);
	for(auto v:adj[u])if(v!=p&&v!=hv[u])hd[v]=v,hld(v,u);
}

Path calc(int u,int i,int v){
	int idx=upper_bound(pos[v].begin(),pos[v].end(),pos[u][i])-pos[v].begin();
	return idx<pos[v].size()?Path(st[v]+idx,0LL):Path(st[v],1LL);
}

int lca(int u,int v){
	while(hd[u]!=hd[v]){
		if(lv[hd[u]]<lv[hd[v]])swap(u,v);
		u=pa[hd[u]];
	}
	return lv[u]<lv[v]?u:v;
}

Path accend(int u,int x,int cur){
	Path res(cur,0);
	int dif=lv[u]-lv[x];
	for(int i=LG-1;i>=0;i--)if(dif>>i&1){
		res=res+up[res.to][i];
	}
	return res;
}

Path decend(int u,int x,int cur){
	Path res(cur,0);
	vector<pair<int,int>> path;
	while(hd[u]!=hd[x]){
		path.emplace_back(u,hd[u]);
		u=pa[hd[u]];
	}
	reverse(path.begin(),path.end());
	int dif=lv[u]-lv[x];
	for(int i=0;i<LG;i++)if(dif>>i&1){
		res=res+down[res.to][i];
	}
	for(auto [node,head]:path){
		res=res+calc(u,res.to-st[u],head);
		dif=lv[node]-lv[head];
		for(int i=0;i<LG;i++)if(dif>>i&1){
			res=res+down[res.to][i];
		}
		u=node;
	}
	return res;
}

ll min_risk(int _n,int _m,int L,vector<int> U,vector<int> V,vector<int> A,vector<int> S){
	n=_n,m=_m;
	for(int i=0;i<n-1;i++){
		adj[U[i]].emplace_back(V[i]);
		adj[V[i]].emplace_back(U[i]);
	}
	dfs(0);
	hld(0);
	for(int i=0;i<m;i++)pos[A[i]].emplace_back(i);
	for(int i=0;i<n;i++)psz[i]=pos[i].size();
	for(int i=0;i<n;i++)st[i+1]=st[i]+psz[i];
	for(int i=0;i<m;i++)up[i][0]=down[i][0]=Path(i,0);
	for(int v=1;v<n;v++){
		int u=pa[v];
		for(int j=0;j<psz[v];j++)up[st[v]+j][0]=calc(v,j,u);
		if(hv[u]==v)for(int j=0;j<psz[u];j++)down[st[u]+j][0]=calc(u,j,v);
	}
	for(int j=1;j<LG;j++)for(int i=0;i<m;i++){
		down[i][j]=down[i][j-1]+down[down[i][j-1].to][j-1];
		up[i][j]=up[i][j-1]+up[up[i][j-1].to][j-1];
	}
	int u=0;
	Path res(0,0);
	for(auto v:S){
		if(u==v)continue;
		int lc=lca(u,v);
		res=res+accend(u,lc,res.to);
		res=res+decend(v,lc,res.to);
		u=v;
	}
	return res.cnt;
}
