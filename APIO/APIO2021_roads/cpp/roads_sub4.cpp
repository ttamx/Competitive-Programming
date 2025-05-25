#include "roads.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

int n;
vector<pair<int,int>> adj[N];
ll dp[N][2];

void dfs(int u,int p,int k){
	ll sum=0;
	vector<ll> a;
	int deg=adj[u].size();
	for(auto [v,w]:adj[u])if(v!=p){
		dfs(v,u,k);
		if(dp[v][0]<dp[v][1]+w){
			sum+=dp[v][0];
			a.emplace_back(dp[v][1]-dp[v][0]+w);
		}else{
			sum+=dp[v][1]+w;
			deg--;
		}
	}
	sort(a.begin(),a.end());
	for(int i=1;i<a.size();i++){
		a[i]+=a[i-1];
	}
	dp[u][0]=dp[u][1]=sum;
	if(deg>k){
		dp[u][0]+=a[deg-k-1];
	}
	if(deg>k+1){
		dp[u][1]+=a[deg-k-2];
	}
}

vector<ll> minimum_closure_costs(int _n,vector<int> _u,vector<int> _v,vector<int> _w){
	n=_n;
	vector<ll> ans(n);
	for(int i=0;i<n-1;i++){
		int u=_u[i],v=_v[i],w=_w[i];
		adj[u].emplace_back(v,w);
		adj[v].emplace_back(u,w);
		ans[0]+=w;
	}
	for(int i=1;i<n;i++){
		dfs(0,-1,i);
		ans[i]=dp[0][0];
	}
	return ans;
}
