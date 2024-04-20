#include "expensive.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e6+5;

int n,q;
vector<pair<int,int>> adj[N];
pair<int,int> dp[N];
int lv[N],pa[N][20];
vector<int> lf;
vector<pair<int,int>> vec,good;

void dfs(int u,int p){
	lv[u]=lv[p]+1;
	pa[u][0]=p;
	for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
	for(auto [v,i]:adj[u]){
		if(v==p)continue;
		dp[v]=dp[u];
		if(i==1)dp[v].first++;
		else dp[v].second++;
		dfs(v,u);
	}
}

int lca(int a,int b){
	if(lv[a]<lv[b])swap(a,b);
	for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
	if(a==b)return a;
	for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
	return pa[a][0];
}

pair<int,int> calc(int u,int v){
	auto [a1,b1]=dp[u];
	auto [a2,b2]=dp[v];
	auto [a3,b3]=dp[lca(u,v)];
	return {a1+a2-2*a3,b1+b2-2*b3};
}

void initialize(int N, int Q, vector<pair<int, int>> R,vector<int> C) {
	n=N,q=Q;
	for(int i=0;i<n-1;i++){
		auto [u,v]=R[i];
		adj[u].emplace_back(v,C[i]);
		adj[v].emplace_back(u,C[i]);
	}
	for(int i=0;i<n;i++)if(adj[i].size()==1)lf.emplace_back(i);
	dfs(0,0);
	for(int i=0;i<lf.size();i++){
		for(int j=0;j<i;j++){
			auto [a,b]=calc(lf[i],lf[j]);
			vec.emplace_back(a,-b);
		}
	}
	sort(vec.begin(),vec.end());
	int pre=-1;
	for(auto [a,b]:vec){
		if(a==pre)continue;
		pre=a,b=-b;
		while(!good.empty()&&good.back().second<=b)good.pop_back();
		good.emplace_back(a,b);
	}
}

long long most_expensive(int x, int y) {
	ll res=0;
	for(auto [a,b]:good)res=max(res,1ll*a*x+1ll*b*y);
	return res;
}