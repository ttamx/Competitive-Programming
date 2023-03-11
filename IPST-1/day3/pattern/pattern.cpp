#include "pattern.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const ll mod=1e9+7;

ll n,m;
ll dp[N];
ll all[N];
ll pow1[N],pow2[N];
vector<int> adj[N];
int lv[N];
bool stop[N];

void predfs(int u,int p){
	lv[u]=lv[p]+1;
	for(auto v:adj[u]){
		predfs(v,u);
	}
}

void dfs(int u){
	dp[u]=1;
	int ch=0;
	ll add=0;
	for(auto v:adj[u]){
		if(stop[v]){
			add+=dp[v];
			continue;
		}
		ch++;
		dfs(v);
		dp[u]=(dp[u]*dp[v])%mod;
	}
	if(ch>1)dp[u]=(dp[u]*((pow1[ch]-pow2[ch]+mod)%mod))%mod;
	if(!stop[u])all[u]=((dp[u]*m)%mod)+add;
	else all[u]=dp[u]+add;
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
	predfs(0,0);
	priority_queue<pair<int,int>> pq;
	for(auto v:p){
		int a=v[0];
		int b=v[1];
		pq.push({lv[a],a});
	}
	vector<ll> ans;
	while(!pq.empty()){
		int i=pq.top().second;
		pq.pop();
		stop[i]=true;
		dfs(i);
		ans.push_back(dp[i]);
	}
	if(stop[0])return (int)all[0];
    dfs(0);
    return (int)all[0];
}
