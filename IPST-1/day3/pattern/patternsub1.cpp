#include "pattern.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const ll mod=1e9+7;

ll n,m;
ll dp[N][7];
ll all[N];
ll pow1[N],pow2[N];
vector<int> adj[N];
vector<int> req;
int fix[N];

set<int> dfs(int u){
	set<int> ret;
	if(fix[u])ret.insert(fix[u]);
	for(auto v:adj[u]){
		set<int> tmp=dfs(v);
		for(auto i:tmp)ret.insert(i);
	}
	return ret;
}

int total_pattern(int N, int M, std::vector<std::vector<int> >Path, std::vector<std::vector<int> >p)
{
	n=N,m=M;
	for(auto v:p){
		fix[v[0]]=v[1];
		req.push_back(v[1]);
	}
	sort(req.begin(),req.end());
	req.erase(unique(req.begin(),req.end()),req.end());
	if(adj[0].size()==1){
	if(req.size()>1)return 0;
	if(req.size()==1){
		return 1;
	}
	return m;
	}
	if(req.size()>2)return 0;
	if(req.size()==2){
		set<int> l=dfs(adj[0][0]),r=dfs(adj[0][1]);
		if(l.size()>1)return 0;
		if(r.size()>1)return 0;
		return 1;
	}
	if(req.size()==1){
		return 2*m-1;
	}
	if(req.size()==0)return (m*m)%mod;
}
