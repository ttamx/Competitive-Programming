#include "crocodile.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1e5+5;
const int inf=2e9;

int n;
p2 dp[N];
bool vis[N];
vector<p2> adj[N];
priority_queue<p2,vector<p2>,greater<p2>> pq;

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]){
	n=N;
	for(int i=0;i<n;i++)dp[i]={inf,inf};
	for(int i=0;i<M;i++){
		int u=R[i][0],v=R[i][1],w=L[i];
		adj[u].emplace_back(v,w);
		adj[v].emplace_back(u,w);
	}
	for(int i=0;i<K;i++){
		dp[P[i]]={0,0};
		pq.emplace(0,P[i]);
	}
	while(!pq.empty()){
		auto [d,u]=pq.top();
		pq.pop();
		if(vis[u])continue;
		vis[u]=true;
		for(auto [v,w]:adj[u]){
			if(d+w<dp[v].second){
				dp[v].second=d+w;
				if(dp[v].second<dp[v].first)swap(dp[v].first,dp[v].second);
				if(dp[v].second<inf)pq.emplace(dp[v].second,v);
			}
		}
	}
	return dp[0].second;
}