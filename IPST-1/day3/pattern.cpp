#include "pattern.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const ll mod=1e9+7;

ll n,m;
ll dp[N];
ll pow1[N],pow2[N];
vector<int> adj[N];

void dfs(int u){
	dp[u]=1;
	int ch=adj[u].size();
	for(auto v:adj[u]){
		dfs(v);
		dp[u]=(dp[u]*dp[v])%mod;
	}
	if(ch>1)dp[u]=(dp[u]*((pow1[ch]-pow2[ch]+mod)%mod))%mod;
}

int total_pattern(int N, int M, std::vector<std::vector<int> >Path, std::vector<std::vector<int> >p)
{
	n=N,m=M;
	pow1[0]=pow2[0]=1;
	for(int i=1;i<=N;i++){
		pow1[i]=(pow1[i-1]*m)%mod;
		pow2[i]=(pow2[i-1]*(m-1))%mod;
	}
	for(auto v:Path)adj[v[0]].push_back(v[1]);
	dfs(0);
    return int((dp[0]*m)%mod);
}
