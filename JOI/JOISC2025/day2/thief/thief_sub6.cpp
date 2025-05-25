#include "thief.h"
#include <bits/stdc++.h>

using namespace std;

void solve(int n,int m,vector<int> _u,vector<int> _v){
	vector<int> tmp(m);
	vector<vector<pair<int,int>>> adj(n);
	for(int i=0;i<m;i++){
		int u=_u[i],v=_v[i];
		adj[u].emplace_back(v,i);
		adj[v].emplace_back(u,~i);
	}
	vector<int> leaves;
	for(int i=0;i<n;i++){
		if(adj[i].size()==1){
			leaves.emplace_back(i);
		}
	}
	function<void(int,int)> dfs=[&](int u,int p){
		for(auto [v,i]:adj[u]){
			if(v==p)continue;
			if(i>=0)tmp[i]=0;
			else tmp[~i]=1;
			dfs(v,u);
		}
	};
	int root=-1;
	for(auto u:leaves){
		dfs(u,-1);
		if(query(tmp)){
			root=u;
			break;
		}
	}
	assert(root!=-1);
	int a=-1,b=-1;
	{
		vector<pair<int,int>> ord;
		vector<bool> vis(n);
		vis[root]=true;
		ord.emplace_back(root,-1);
		for(int i=0;i<ord.size();i++){
			int u=ord[i].first;
			for(auto [v,i]:adj[u]){
				if(!vis[v]){
					vis[v]=true;
					ord.emplace_back(v,i);
				}
			}
		}
		assert(ord.size()==n);
		int l=1,r=n-1;
		while(l<r){
			int mid=(l+r)/2;
			for(int i=1;i<n;i++){
				int j=ord[i].second;
				if(i>mid)j=~j;
				if(j>=0)tmp[j]=0;
				else tmp[~j]=1;
			}
			if(query(tmp))r=mid;
			else l=mid+1;
		}
		b=ord[l].first;
	}
	root=b;
	{
		vector<pair<int,int>> ord;
		vector<bool> vis(n);
		vis[root]=true;
		ord.emplace_back(root,-1);
		for(int i=0;i<ord.size();i++){
			int u=ord[i].first;
			for(auto [v,i]:adj[u]){
				if(!vis[v]){
					vis[v]=true;
					ord.emplace_back(v,~i);
				}
			}
		}
		assert(ord.size()==n);
		int l=1,r=n-1;
		while(l<r){
			int mid=(l+r)/2;
			for(int i=1;i<n;i++){
				int j=ord[i].second;
				if(i>mid)j=~j;
				if(j>=0)tmp[j]=0;
				else tmp[~j]=1;
			}
			if(query(tmp))r=mid;
			else l=mid+1;
		}
		a=ord[l].first;
	}
	answer(a,b);
}
