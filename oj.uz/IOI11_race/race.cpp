#include "race.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=2e5+5;
const int K=1e6+5;

int n,k;
int ans;
vector<p2> adj[N];
int sz[N];
bool used[N];
int dist[K];
vector<int> res;
vector<p2> res2;

int dfssz(int u,int p=-1){
	sz[u]=1;
	for(auto [v,w]:adj[u])if(v!=p&&!used[v])sz[u]+=dfssz(v,u);
	return sz[u];
}

int centroid(int u,int cnt,int p=-1){
	for(auto [v,w]:adj[u])if(v!=p&&!used[v]&&sz[v]*2>cnt)return centroid(v,cnt,u);
	return u;
}

void dfs(int u,int d,int cnt,int p=-1){
	if(d>k)return;
	res.emplace_back(d);
	res2.emplace_back(d,cnt);
	ans=min(ans,cnt+dist[k-d]);
	for(auto [v,w]:adj[u])if(v!=p&&!used[v])dfs(v,d+w,cnt+1,u);
}

void decom(int u){
	u=centroid(u,dfssz(u));
	used[u]=true;
	for(auto [v,w]:adj[u]){
		if(used[v])continue;
		dfs(v,w,1,u);
		for(auto [x,y]:res2)dist[x]=min(dist[x],y);
		res2.clear();
	}
	for(auto i:res)dist[i]=n;
	res.clear();
	for(auto [v,w]:adj[u])if(!used[v])decom(v);
}

int best_path(int N, int K, int H[][2], int L[]){
	n=N,k=K;
	ans=n;
	for(int i=1;i<=k;i++)dist[i]=n;
	for(int i=0;i<n-1;i++){
		int u=H[i][0],v=H[i][1],w=L[i];
		adj[u].emplace_back(v,w);
		adj[v].emplace_back(u,w);
	}
	decom(0);
	return (ans==n?-1:ans);
}