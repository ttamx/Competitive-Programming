#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,t;
    cin >> n >> m >> t;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> tin(n),tout(n);
    int timer=0;
    function<void(int,int)> dfs=[&](int u,int p){
        tin[u]=++timer;
        for(auto v:adj[u])if(v!=p)dfs(v,u);
        tout[u]=timer;
    };
    for(int i=0;i<t;i++){
        int r;
        cin >> r;
        dfs(r-1,-1);
    }
    int q;
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        u--,v--;
        cout << (tin[v]<=tin[u]&&tout[u]<=tout[v]?"YES":"NO") << "\n";
    }
}