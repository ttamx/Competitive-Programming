#include "split.h"
#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
vector<int> adj[N];
int disc[N],low[N],sz[N];
int timer=0;
bool vis[N];

void dfs(int u,int p=-1){
	disc[u]=low[u]=++timer;
	sz[u]=1;
	for(auto v:adj[u]){
		if(!disc[v]){
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			sz[u]+=sz[v];
		}else if(v!=p){
			low[u]=min(low[u],disc[v]);
		}
	}
}

vector<int> find_split(int _n,int a,int b,int c,vector<int> p,vector<int> q){
	n=_n;
	for(int i=0;i<p.size();i++){
		int u=p[i],v=q[i];
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	dfs(0);
	pair<int,int> d[3]={{a,1},{b,2},{c,3}};
	sort(d,d+3);
	a=d[0].first,b=d[1].first;
	for(int u=1;u<n;u++){
		bool ok=sz[u]>=a;
		for(auto v:adj[u])if(disc[v]>disc[u])ok&=sz[v]<a;
		if(!ok)continue;
		vector<int> del;
		int cur=sz[u];
		for(auto v:adj[u])if(disc[v]>disc[u]&&low[v]<disc[u]&&cur-sz[v]>=a){
			del.emplace_back(v);
			cur-=sz[v];
		}
		if(n-cur<a)continue;
		vector<int> ans(n,d[2].second);
		if(cur>n-cur)swap(d[0],d[1]);
		for(auto x:del)vis[x]=true;
		queue<int> q;
		vis[u]=true;
		q.emplace(u);
		for(int i=0;i<d[0].first;i++){
			int x=q.front();
			q.pop();
			ans[x]=d[0].second;
			for(auto v:adj[x])if(disc[v]>disc[x]&&!vis[v]){
				vis[v]=true;
				q.emplace(v);
			}
		}
		while(!q.empty())q.pop();
		for(int i=0;i<n;i++)vis[i]=false;
		vis[0]=true;
		q.emplace(0);
		for(int i=0;i<d[1].first;i++){
			int x=q.front();
			q.pop();
			ans[x]=d[1].second;
			for(auto v:adj[x])if(!vis[v]&&ans[v]==d[2].second){
				vis[v]=true;
				q.emplace(v);
			}
		}
		return ans;
	}
	return vector<int>(n);
}