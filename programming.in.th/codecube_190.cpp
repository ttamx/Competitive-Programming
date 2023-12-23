#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,cnt;
int disc[N],low[N],dp[N];
bool vis[N];
vector<int> adj[N];
vector<pair<int,int>> e;

void tarj(int u,int p){
    disc[u]=low[u]=++cnt;
    vis[u]=true;
    for(auto v:adj[u]){
        if(!vis[v]){
            tarj(v,u);
            low[u]=min(low[u],low[v]);
        }else if(v!=p){
            low[u]=min(low[u],disc[v]);
        }
    }
}

void dfs(int u){
    vis[u]=true;
    for(auto v:adj[u]){
        if(vis[v])continue;
        dfs(v);
        dp[u]+=dp[v];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    e.resize(m);
    for(auto &[u,v]:e){
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    tarj(1,1);
    for(int i=1;i<=n;i++){
        adj[i].clear();
        vis[i]=false;
        dp[low[i]]++;
    }
    for(auto [u,v]:e){
        u=low[u],v=low[v];
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    for(auto [u,v]:e){
        u=low[u],v=low[v];
        if(dp[u]>dp[v])swap(u,v);
        cout << (u==v?0:1ll*dp[u]*(n-dp[u])) << ' ';
    }
}