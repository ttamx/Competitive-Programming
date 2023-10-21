#include "twohomes.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1005;

int n,m;
vector<p2> adj[N];

bool ask(vector<int> a){
	vector<bool> ok(m);
	for(auto x:a)ok[x]=true;
	vector<int> res;
	for(int i=0;i<m;i++)if(!ok[i])res.emplace_back(i);
	return is_reachable(res);
}

int solve(int rt){
	vector<bool> vis(n);
	vector<p2> q;
	q.emplace_back(rt,-1);
	vis[rt]=true;
	for(int i=0;i<q.size();i++){
		int u=q[i].first;
		for(auto [v,j]:adj[u])if(!vis[v]){
			vis[v]=true;
			q.emplace_back(v,j);
		}
	}
	int l=0,r=q.size()-1;
	while(l<r){
		int mid=(l+r)/2;
		vector<int> res;
		for(int i=1;i<=mid;i++)res.emplace_back(q[i].second);
		if(ask(res))r=mid;
		else l=mid+1;
	}
	return q[l].first;
}

p2 find_homes(int N,int M,vector<vector<int>> R){
	n=N,m=M;
	for(int i=0;i<m;i++){
		int u=R[i][0],v=R[i][1];
		adj[u].emplace_back(v,i);
		adj[v].emplace_back(u,i);
	}
	int s=solve(0);
	int t=solve(s);
	return p2(s,t);
}