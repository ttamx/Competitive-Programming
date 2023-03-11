#include "onepath.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

int n,m,q;
int p[N],p2[N],lv[N],pa[N][20],pid[N];
vector<pair<int,int>> adj[N];
bool loop[N];

int fp(int u){
	if(p[u]==u)return u;
	return p[u]=fp(p[u]);
}

int fp2(int u){
	if(p2[u]==u)return u;
	return p2[u]=fp2(p2[u]);
}

void dfs(int u,int p,int idx){
	lv[u]=lv[p]+1;
	pa[u][0]=p;
	pid[u]=idx;
	for(int i=1;i<=17;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
	for(auto [v,i]:adj[u]){
		if(v==p)continue;
		dfs(v,u,i);
	}
}

int lca(int a,int b){
	if(lv[a]<lv[b])swap(a,b);
	for(int i=17;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
	if(a==b)return a;
	for(int i=17;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
	return pa[a][0];
}

void updateup(int u,int v){
	if(lv[u]<=lv[v])return;
	p[fp(u)]=fp(v);
	loop[pid[u]]=true;
	updateup(fp(pa[u][0]),v);
}

void initialize(int N, int M, int Q, vector<pair<int,int>> r) {
	n=N,m=M,q=Q;
	queue<pair<int,int>> qu;
	iota(p,p+n,0);
	iota(p2,p2+n,0);
	int idx=0;
	for(auto [u,v]:r){
		int pu=fp(u),pv=fp(v);
		if(pu!=pv){
			p[pu]=pv;
			adj[u].push_back({v,idx});
			adj[v].push_back({u,idx});
			idx++;
		}else{
			qu.push({u,v});
		}
	}
	dfs(0,0,0);
	while(!qu.empty()){
		auto [u,v]=qu.front();
		qu.pop();
		int l=lca(u,v);
	}
	return;
}

bool is_dangerous(int u, int v) {
	int l=lca(u,v);
	return u==v;
}

void build_road(int u, int v) {
	int l=lca(u,v);
	return;
}

