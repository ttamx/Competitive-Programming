#include "grader.h"
#include "encoder.h"
#include<bits/stdc++.h>

using namespace std;

void encode(int n, int h, int ne, int *v1, int *v2){
	vector<vector<int>> adj(n);
	for(int i=0;i<ne;i++){
		int u=v1[i],v=v2[i];
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	vector<bool> vis(n);
	vector<int> p(n);
	function<void(int)> dfs=[&](int u){
		vis[u]=true;
		for(auto v:adj[u]){
			if(vis[v])continue;
			p[v]=u;
			dfs(v);
		}
	};
	dfs(0);
	for(int i=1;i<n;i++)for(int j=0;j<10;j++)encode_bit(p[i]>>j&1);
	vector<vector<pair<int,int>>> adj2(n);
	for(int i=1;i<n;i++){
		int u=i,v=p[i];
		adj2[u].emplace_back(v,i-1);
		adj2[v].emplace_back(u,i-1);
	}
	for(int i=0;i<h;i++){
		vector<int> dist(n,2e9);
		queue<int> q;
		q.emplace(i);
		dist[i]=0;
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(auto v:adj[u]){
				if(dist[v]<=dist[u]+1)continue;
				dist[v]=dist[u]+1;
				q.emplace(v);
			}
		}
		vector<int> val(n-1);
		function<void(int,int)> dfs2=[&](int u,int p){
			for(auto [v,id]:adj2[u]){
				if(v==p)continue;
				val[id]=dist[v]-dist[u];
				dfs2(v,u);
			}
		};
		dfs2(i,-1);
		while(val.size()%5!=0)val.emplace_back(0);
		int cur=0,cnt=0;
		for(auto x:val){
			cur*=3;
			cur+=x+1;
			cnt++;
			if(cnt==5){
				for(int j=0;j<8;j++)encode_bit(cur>>j&1);
				cur=cnt=0;
			}
		}
	}
}