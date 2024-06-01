#include"september.h"
#include<bits/stdc++.h>

using namespace std;

int solve(int n,int m,vector<int> f,vector<vector<int>> s){
	vector<vector<int>> adj(n);
	for(int i=1;i<n;i++)adj[f[i]].emplace_back(i);
	vector<vector<bool>> vis(n,vector<bool>(5));
	vector<bool> added(n);
	vector<int> cnt(n);
	multiset<int> ms;
	int bad=0;
	function<void(int,int)> dfs=[&](int u,int i){
		if(vis[u][i])return;
		vis[u][i]=true;
		if(!added[u]){
			added[u]=true;
			for(int i=0;i<m;i++)ms.emplace(u);
		}
		for(auto v:adj[u])dfs(v,i);
	};
	int ans=0;
	for(int i=0;i<n-1;i++){
		for(int j=0;j<m;j++)dfs(s[j][i],j);
		for(int j=0;j<m;j++)ms.erase(ms.find(s[j][i]));
		ans+=ms.empty();
	}
	return ans;
}
