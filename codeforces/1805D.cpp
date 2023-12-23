#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,cnt;
int ans[N];
pair<int,int> dp[N],dp2[N];
vector<int> adj[N];
bool used[N];
vector<pair<int,int>> vec;

void dfs(int u,int p=0){
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        dp2[u]=max(dp2[u],{dp[v].first+1,v});
        if(dp2[u]>dp[u])swap(dp[u],dp2[u]);
    }
}

void dfs2(int u,int p=0){
    for(auto v:adj[u]){
        if(v==p)continue;
        int res=(dp2[u].first!=v?dp[u]:dp2[u]).first;
        dp2[v]=max(dp2[v],{dp[u].first+1,u});
        if(dp2[v]>dp[v])swap(dp[v],dp2[v]);
        dfs2(v,u);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    for(int i=1;i<=n;i++)cout << ans[i] << " \n"[i==n];
}