#include "zebra.h"
#include <bits/stdc++.h>

using namespace std;

const int N=505;

int n,rt;
vector<pair<int,int>> adj[N];
bool blocked[N];
int par[N];
pair<int,int> dist[N];

void dfs(int u,int p=-1){
	par[u]=p;
	for(auto [v,i]:adj[u])if(v!=p&&!blocked[v]){
		dist[v]={dist[u].first+1,i};
		dfs(v,u);
	}
}

bool is_root(int u){
	vector<int> path[2];
	int leaf=0;
	function<void(int,int,int)> dfs=[&](int u,int p,int d){
		int lf=1;
		for(auto [v,i]:adj[u])if(v!=p){
			lf=0;
			path[d].emplace_back(i);
			dfs(v,u,d^1);
		}
		leaf+=lf;
	};
	dfs(u,u,1);
	return leaf>=3&&!is_zebra(path[0])&&!is_zebra(path[1]);
}

int solve(int u){
	blocked[u]=false;
	for(int i=0;i<n;i++)dist[i]={-1,-1};
	dist[u]={0,-1};
	dfs(u);
	u=max_element(dist,dist+n)-dist;
	for(int i=0;i<n;i++)dist[i]={-1,-1};
	dist[u]={0,-1};
	dfs(u);
	int v=max_element(dist,dist+n)-dist;
	for(int i=0;i<n;i++)if(dist[i].first!=-1)cerr << par[i] << " > " << i << "\n";
	if(is_root(u))return u;
	if(is_root(v))return v;
	vector<pair<int,int>> path;
	for(int x=v;x!=u;x=par[x])path.emplace_back(x,dist[x].second);
	reverse(path.begin(),path.end());
	cerr << u;
	for(auto [x,i]:path)cerr << " -> " << x;
	cerr << "\n";
	int l=1,r=(path.size()+1)/2;
	int bound=r;
	while(l<r){
		int m=(l+r)/2;
		vector<int> tmp;
		for(int i=0;i<=m;i++){
			tmp.emplace_back(path[i*2].second);
		}
		if(is_zebra(tmp))r=m;
		else l=m+1;
	}
	for(int x=v;x!=-1;x=par[x])blocked[x]=true;
	if(l==bound)return solve(par[v]);
	cerr << "FOUND " << path[l*2].first << "\n";
	if(is_zebra({path[l*2].second,path[l*2-1].second}))return solve(path[l*2-2].first);
	else return solve(path[l*2-1].first);
}

int find_root(int _n,vector<int> U,vector<int> V){
	n=_n;
	for(int i=0;i<n-1;i++){
		adj[U[i]].emplace_back(V[i],i);
		adj[V[i]].emplace_back(U[i],i);
	}
	return solve(0);
}
