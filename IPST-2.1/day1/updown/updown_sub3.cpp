#include "updown.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

vector<int> adj[N];

int idx;
int mp[N];
int dp[N][2],dp2[N][2];

void dfs(int u,int p){
    mp[idx++]=u;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
    }
}

vector<int> updown(int n, int m, vector<int> U, vector<int> V) {
	assert(m==n-1);
	for(int i=0;i<m;i++){
		adj[U[i]].emplace_back(V[i]);
		adj[V[i]].emplace_back(U[i]);
	}
    for(int i=0;i<n;i++){
        if(adj[i].size()==1){
            dfs(i,-1);
            break;
        }
    }
    for(int i=1;i<n;i++){
        if(mp[i]>mp[i-1])dp[i][0]=max(dp[i][0],1+dp[i-1][1]);
        if(mp[i]<mp[i-1])dp[i][1]=max(dp[i][1],1+dp[i-1][0]);
    }
    for(int i=n-2;i>=0;i--){
        if(mp[i]>mp[i+1])dp2[i][0]=max(dp2[i][0],1+dp2[i+1][1]);
        if(mp[i]<mp[i+1])dp2[i][1]=max(dp2[i][1],1+dp2[i+1][0]);
    }
	vector<int> ans(n);
    for(int i=0;i<n;i++)ans[mp[i]]=dp[i][0]+dp[i][1]+dp2[i][0]+dp2[i][1];
	return ans;
}