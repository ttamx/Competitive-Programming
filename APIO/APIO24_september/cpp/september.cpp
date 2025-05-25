#include"september.h"
#include<bits/stdc++.h>
 
using namespace std;
 
int solve(int n,int m,vector<int> f,vector<vector<int>> s){
	vector<vector<int>> adj(n);
	for(int i=1;i<n;i++)adj[f[i]].emplace_back(i);
	vector<vector<bool>> vis(n,vector<bool>(m));
	vector<bool> add(n);
	int cnt=0;
	function<void(int,int)> dfs=[&](int u,int i){
		if(vis[u][i])return;
		vis[u][i]=true;
		if(!add[u])add[u]=true,cnt++;
		for(auto v:adj[u])dfs(v,i);
	};
	int ans=0;
	for(int i=0;i<n-1;i++){
		for(int j=0;j<m;j++)dfs(s[j][i],j);
		ans+=--cnt==0;
	}
	return ans;
}