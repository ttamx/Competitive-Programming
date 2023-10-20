#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m;
int dp[N];
vector<pair<int,int>> adj[N];

void dfs(int u,int p){
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        dp[v]=dp[u]^w;
        dfs(v,u);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dfs(1,0);
    while(m--){
        int u,v;
        cin >> u >> v;
        cout << (dp[u]^dp[v]) << '\n';
    }
}