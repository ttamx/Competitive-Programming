#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<pair<int,int>>> adj(n);
    for(int u=1;u<n;u++){
        int v,w;
        cin >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<int> par(n),dep(n),jump(n);
    vector<long long> dist(n);
    function<void(int)> dfs=[&](int u){
        int t=(dep[u]-dep[jump[u]]==dep[jump[u]]-dep[jump[jump[u]]]?jump[jump[u]]:u);
        for(auto [v,w]:adj[u])if(v!=par[u]){
            par[v]=u;
            dep[v]=dep[u]+1;
            jump[v]=t;
            dist[v]=dist[u]+w;
            dfs(v);
        }
    };
    dfs(0);
    auto lca=[&](int u,int v){
        if(dep[u]<dep[v])swap(u,v);
        while(dep[u]>dep[v])u=(dep[jump[u]]>=dep[v]?jump[u]:par[u]);
        while(u!=v){
            if(jump[u]!=jump[v])u=jump[u],v=jump[v];
            else u=par[u],v=par[v];
        }
        return u;
    };
    int q;
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        cout << dist[u]+dist[v]-2*dist[lca(u,v)] << "\n";
    }
}