#include "conveyor.h"
#include<bits/stdc++.h>
#include "grader.cpp"

using namespace std;

void Solve(int n, vector<int> A, vector<int> B) {
	vector<int> ans(n - 1, 0);
	vector<pair<int,int>> edge(n-1);
	vector<vector<int>> adj(n);
	for(int i=0;i<n-1;i++){
		auto &[u,v]=edge[i];
		u=A[i];
		v=B[i];
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	vector<bool> vis(n);
	vector<int> q,p(n);
	q.emplace_back(0);
	vis[0]=true;
	for(int i=0;i<q.size();i++){
		int u=q[i];
		for(auto v:adj[u]){
			if(vis[v])continue;
			cerr << u << "->" << v << "\n";
			vis[v]=true;
			p[v]=u;
			q.emplace_back(v);
		}
	}
	vector<int> mp(n);
	for(int i=1;i<n-1;i++){
		auto [u,v]=edge[i];
		if(p[u]!=v)swap(u,v);
		mp[u]=i;
	}
	vector<int> rev(n-1);
	for(int id=n-1;id>0;id--){
		int i=q[id];
		auto [u,v]=edge[mp[i]];
		vector<int> y(n);
		if(p[u]==v){
			y[u]=1;
			auto res=Query(rev,y);
			if(res[u]==1){
				ans[mp[i]]=1;
				rev[mp[i]]=1;
			}else{
				ans[mp[i]]=0;
				rev[mp[i]]=0;
			}
		}else{
			y[v]=1;
			auto res=Query(rev,y);
			if(res[v]==1){
				ans[mp[i]]=0;
				rev[mp[i]]=1;
			}else{
				ans[mp[i]]=1;
				rev[mp[i]]=0;
			}
		}
	}
	Answer(ans);
}