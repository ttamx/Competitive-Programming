#include "icecream.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5005;
const int MOD=1e9+7;

int n;
int p[N];
vector<int> adj[N];
int root=-1;
int sz[N],pre_sz[N],suf_sz[N];
ll ways[N],C[N][N],pre[N],suf[N],exc[N];
ll dp[N][N];

void dfs(int u){
    ways[u]=1;
    for(auto v:adj[u]){
        dfs(v);
        sz[u]+=sz[v];
        ways[u]=ways[u]*C[sz[u]][sz[v]]%MOD*ways[v]%MOD;
    }
    sz[u]++;
}

void dfs2(int u){
    for(int t=0;t<2;t++){
        int cur_sz=0;
        ll cur_dp=1;
        for(auto v:adj[u]){
            (t?suf[v]:pre[v])=cur_dp;
            (t?suf_sz[v]:pre_sz[v])=cur_sz;
            cur_sz+=sz[v];
            cur_dp=cur_dp*C[cur_sz][sz[v]]%MOD*ways[v]%MOD;
        }
        reverse(adj[u].begin(),adj[u].end());
    }
    for(auto v:adj[u]){
        exc[v]=pre[v]*suf[v]%MOD*C[pre_sz[v]+suf_sz[v]][pre_sz[v]]%MOD;
        int s=n-sz[u]+1;
        int ss=sz[u]-sz[v]-1;
        ll sum=0;
        for(int i=0;i<=s+ss;i++){
            dp[v][i]=exc[v]*sum%MOD;
            sum=(sum+dp[u][i]*C[s-i-1+ss][ss])%MOD;
        }
        dfs2(v);
    }
}

void initialize(int _n,int Q,vector<int> _p){
    n=_n;
    for(int i=0;i<=n;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++){
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
        }
    }
    for(int i=0;i<n;i++){
        p[i]=_p[i];
        if(p[i]==-1)root=i;
        else adj[p[i]].emplace_back(i);
    }
    dfs(root);
    dp[root][0]=1;
    dfs2(root);
}

long long count_perm(int v,int l1,int r1,int l2,int r2){
    int u=p[v];
    int s=n-sz[u]+1;
    int ss=sz[u]-sz[v]-1;
    ll sum=0,ans=0;
    for(int i=0;i<=r1;i++){
        if(i>=l1)ans=(ans+exc[v]*sum%MOD*ways[v]%MOD*C[n-i-1][sz[v]-1])%MOD;
        if(l2<=i&&i<=r2&&i<=s+ss)sum=(sum+dp[u][i]*C[s-i-1+ss][ss])%MOD;
    }
    return ans;
}