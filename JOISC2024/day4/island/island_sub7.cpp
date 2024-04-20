#include "island.h"
#include<bits/stdc++.h>

using namespace std;

void solve(int N,int L){
	vector<vector<int>> memo(N+2,vector<int>(N+2));
	vector<bool> vis(N+2);
	auto ask=[&](int u,int i){
		if(memo[u][i])return memo[u][i];
		return memo[u][i]=query(u,i);
	};
	function<void(int,int)> dfs=[&](int u,int p){
		vector<int> ch;
		for(int i=1;i<N;i++){
			int v=ask(u,i);
			if(v==p)continue;
			if(vis[v])break;
			bool bad=false;
			for(int j=1;j<N;j++){
				int x=ask(v,j);
				if(vis[x]){
					if(x==u){
						answer(u,v);
						vis[v]=true;
						ch.emplace_back(v);
					}else{
						bad=true;
					}
					break;
				}
			}
			if(bad)break;
		}
		for(auto x:ch)dfs(x,u);
	};
	vis[1]=true;
	dfs(1,0);
}