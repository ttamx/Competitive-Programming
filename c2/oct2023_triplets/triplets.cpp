#include "triplets.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int mod=9377;

int n,m;
int c[N];
vector<int> adj[N],rev[N];
bool vis[N];
stack<int> s,vec;
int cnt[N];

void dfs(int u){
	if(vis[u])return;
	vis[u]=true;
	for(auto v:adj[u])dfs(v);
	s.emplace(u);
}

void kos(int u){
	if(vis[u])return;
	vis[u]=true;
	cnt[c[u]]++;
	vec.emplace(c[u]);
	for(auto v:rev[u])kos(v);
}

int calc(int x){
	x%=mod;
	return x*(x-1)%mod*(x-2)%mod;
}

int count_triplets(int N, vector<int> U, vector<int> V, vector<int> C){
	n=N,m=U.size();
	for(int i=0;i<n;i++)c[i]=C[i];
	for(int i=0;i<m;i++){
		int u=U[i],v=V[i];
		adj[u].emplace_back(v);
		rev[v].emplace_back(u);
	}
	int ans=calc(n);
	for(int i=0;i<n;i++)dfs(i);
	for(int i=0;i<n;i++)vis[i]=false;
	while(!s.empty()){
		int u=s.top();
		s.pop();
		kos(u);
		while(!vec.empty()){
			int x=vec.top();
			vec.pop();
			ans+=mod-calc(cnt[x]);
			ans%=mod;
			cnt[x]=0;
		}
	}
	return ans;
}