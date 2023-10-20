#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
vector<pair<int,int>> adj[N];
int lv[N],pa[N][20];
long long dp[N];

void dfs(int u,int p){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        dp[v]=dp[u]+w;
        dfs(v,u);
    }
}

int lca(int u,int v){
    if(lv[u]<lv[v])swap(u,v);
    for(int i=19;i>=0;i--)if(lv[pa[u][i]]>=lv[v])u=pa[u][i];
    if(u==v)return u;
    for(int i=19;i>=0;i--)if(pa[u][i]!=pa[v][i])u=pa[u][i],v=pa[v][i];
    return pa[u][0];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int u=1;u<n;u++){
        int v,w;
        cin >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dfs(0,0);
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        cout << dp[u]+dp[v]-2*dp[lca(u,v)] << "\n";
    }
}