#include <bits/stdc++.h>
#include "disappear.h"

using namespace std;

int miku(int n,int m,vector<int> _u,vector<int> _v){
	vector<vector<int>> adj(n);
	for(int i=0;i<m;i++){
		int u=_u[i],v=_v[i];
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	vector<int> a;
	vector<bool> vis(n);
	for(int i=0;i<n;i++)if(adj[i].size()>1){
		a.emplace_back(i);
		vis[i]=true;
		break;
	}
	for(int i=0;i<a.size();i++)for(auto v:adj[a[i]])if(!vis[v])vis[v]=true,a.emplace_back(v);
	auto ask=[&](int i){
		if(i==0)return detect({a[0],a[2]});
		return detect(vector<int>(a.begin(),a.begin()+i+1));
	};
	int l=0,r=n-1;
	while(l<r){
		int m=(l+r)/2;
		if(ask(m))r=m;
		else l=m+1;
	}
	return a[l];
}