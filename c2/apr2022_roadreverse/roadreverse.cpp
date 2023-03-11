#include "roadreverse.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=12;

int n,m,k;
int degin[N];
int line[N],pos[N];
vector<int> adj[N];
vector<pair<int,int>> edge,edge2;
pair<int,int> mn[N][K],mx[N][K];

int count_roads(int N, int M, int K,vector<vector<int>> S,vector<pair<int,int>> R){
	n=N,m=M,k=K;
	line[0]=k;
	for(int i=0;i<n;i++)for(int j=0;j<k;j++)mn[i][j]={n,n},mx[i][j]={-1,-1};
	for(int i=0;i<k;i++){
		int u=0;
		mn[0][i].first=mx[0][i].first=0;
		for(int j=0;j<S[i].size();j++){
			int v=S[i][j];
			line[v]=i;
			pos[v]=j+1;
			mn[v][i].first=mx[v][i].first=j+1;
			adj[u].push_back(v);
			edge2.push_back({u,v});
			degin[v]++;
			u=v;
		}
	}
	for(auto [u,v]:R){
		adj[u].push_back(v);
		edge.push_back({u,v});
		degin[v]++;
	}
	queue<int> topo;
	stack<int> revtopo;
	topo.push(0);
	while(!topo.empty()){
		int u=topo.front();
		topo.pop();
		revtopo.push(u);
		for(auto v:adj[u]){
			for(int i=0;i<k;i++){
				if(i==line[v])continue;
				if(mx[v][i].first<mx[u][i].first){
					mx[v][i].second=max(mx[v][i].first,mx[u][i].second);
					mx[v][i].first=mx[u][i].first;
				}else{
					mx[v][i].second=max(mx[v][i].second,mx[u][i].first);
				}
			}
			if(--degin[v]==0)topo.push(v);
		}
	}
	while(!revtopo.empty()){
		int u=revtopo.top();
		revtopo.pop();
		for(auto v:adj[u]){
			for(int i=0;i<k;i++){
				if(u==0||i==line[u])continue;
				if(mn[u][i].first>mn[v][i].first){
					mn[u][i].second=min(mn[u][i].first,mn[v][i].second);
					mn[u][i].first=mn[v][i].first;
				}else{
					mn[u][i].second=min(mn[u][i].second,mn[v][i].first);
				}
			}
		}
	}
	int ans=0;
	for(auto [u,v]:edge){
		for(int i=0;i<k;i++){
			int maxx=mx[v][i].first,minn=mn[u][i].first;
			if(maxx==mx[u][i].first)maxx=mx[v][i].second;
			if(minn==mn[v][i].first)minn=mn[u][i].second;
			if(minn<=maxx){
				ans++;
				break;
			}
		}
	}
	for(auto [u,v]:edge2){
		for(int i=0;i<k;i++){
			if(i==line[v])continue;
			int maxx=mx[v][i].first,minn=mn[u][i].first;
			if(maxx==mx[u][i].first)maxx=mx[v][i].second;
			if(minn==mn[v][i].first)minn=mn[u][i].second;
			if(minn<=maxx){
				ans++;
				break;
			}
		}
	}
	return m-ans;
}
