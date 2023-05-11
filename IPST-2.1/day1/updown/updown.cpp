#include "updown.h"
#include<bits/stdc++.h>

using namespace std;

const int N=2005;

vector<int> adj[N];

vector<int> updown(int n, int m, vector<int> U, vector<int> V) {
	assert(n<=2000);
	for(int i=0;i<m;i++){
		adj[U[i]].emplace_back(V[i]);
		adj[V[i]].emplace_back(U[i]);
	}
	vector<int> ans(n);
	for(int i=0;i<n;i++){
		vector<vector<bool>> vis(n,vector<bool>(2));
		queue<pair<int,int>> q;
		q.emplace(i,0);
		q.emplace(i,1);
		vis[i][0]=vis[i][1]=true;
		while(!q.empty()){
			auto [u,d]=q.front();
			q.pop();
			for(auto v:adj[u]){
				if(d==1&&v<u)continue;
				if(d==0&&v>u)continue;
				if(vis[v][d^1])continue;
				vis[v][d^1]=true;
				q.emplace(v,d^1);
			}
		}
		ans[i]=-1;
		for(int j=0;j<n;j++)if(vis[j][0]||vis[j][1])ans[i]++;
	}
	return ans;
}