#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> fa(n);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    };
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(fp(u)==fp(v))continue;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        fa[fp(v)]=fp(u);
    }
    vector<int> deg(n);
    int q;
    cin >> q;
    vector<pair<int,int>> qr(q);
    for(auto &[u,v]:qr){
        cin >> u >> v;
        u--,v--;
        deg[u]^=1;
        deg[v]^=1;
    }
    int tot=accumulate(deg.begin(),deg.end(),0);
    if(tot){
        cout << "NO\n";
        cout << tot/2 << "\n";
        exit(0);
    }
    vector<int> dep(n),par(n,-1);
    function<void(int)> dfs=[&](int u){
        for(auto v:adj[u]){
            if(v==par[u])continue;
            par[v]=u;
            dep[v]=dep[u]+1;
            dfs(v);
        }
    };
    dfs(0);
    cout << "YES\n";
    for(auto [u,v]:qr){
        vector<int> pu,pv;
        while(u!=v){
            if(dep[u]>dep[v]){
                pu.emplace_back(u);
                u=par[u];
            }else{
                pv.emplace_back(v);
                v=par[v];
            }
        }
        pu.emplace_back(u);
        reverse(pv.begin(),pv.end());
        pu.insert(pu.end(),pv.begin(),pv.end());
        cout << pu.size() << "\n";
        for(auto x:pu){
            cout << x+1 << " ";
        }
        cout << "\n";
    }
}