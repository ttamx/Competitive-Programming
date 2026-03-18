#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> edges(m);
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        auto &[u,v]=edges[i];
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    vector<int> disc(n),low(n);
    vector<int> f(m);
    int timer=0;
    function<void(int,int)> dfs=[&](int u,int p){
        disc[u]=low[u]=++timer;
        int ch=0;
        for(auto [v,i]:adj[u]){
            if(!disc[v]){
                ch++;
                f[i]=1;
                dfs(v,u);
                low[u]=min(low[u],low[v]);
                if(low[v]>disc[u]){
                    cout << 0 << "\n";
                    exit(0);
                }
            }else if(v!=p){
                low[u]=min(low[u],disc[v]);
            }
        }
    };
    dfs(0,-1);
    for(int i=0;i<m;i++){
        auto [u,v]=edges[i];
        if(disc[u]>disc[v])swap(u,v);
        if(f[i])swap(u,v);
        cout << u+1 << " " << v+1 << "\n";
    }
}