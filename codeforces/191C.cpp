#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    vector<int> par(n),jump(n),dep(n);
    function<void(int)> dfs=[&](int u){
        for(auto [v,i]:adj[u]){
            if(v==par[u]){
                continue;
            }
            par[v]=u;
            jump[v]=(dep[u]-dep[jump[u]]==dep[jump[u]]-dep[jump[jump[u]]]?jump[jump[u]]:u);
            dep[v]=dep[u]+1;
            dfs(v);
        }
    };
    auto lca=[&](int u,int v){
        if(dep[u]<dep[v])swap(u,v);
        while(dep[u]>dep[v])u=dep[jump[u]]>=dep[v]?jump[u]:par[u];
        while(u!=v){
            if(jump[u]!=jump[v])u=jump[u],v=jump[v];
            else u=par[u],v=par[v];
        }
        return u;
    };
    dfs(0);
    int q;
    cin >> q;
    vector<int> a(n);
    for(int i=0;i<q;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        a[u]++;
        a[v]++;
        a[lca(u,v)]-=2;
    }
    vector<int> ans(n-1);
    function<void(int)> dfs2=[&](int u){
        for(auto [v,i]:adj[u]){
            if(v==par[u]){
                continue;
            }
            dfs2(v);
            ans[i]=a[v];
            a[u]+=a[v];
        }
    };
    dfs2(0);
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}