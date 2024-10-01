#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> fa(n+m);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    };
    vector<vector<int>> adj(n+m);
    for(int i=0;i<n;i++){
        int k;
        cin >> k;
        for(int j=0;j<k;j++){
            int x;
            cin >> x;
            x--;
            if(fp(x)!=fp(i+m)){
                adj[x].emplace_back(i+m);
                adj[i+m].emplace_back(x);
                fa[fp(x)]=fp(i+m);
            }
        }
    }
    vector<int> dep(n+m),par(n+m,-1);
    function<void(int)> dfs=[&](int u){
        for(auto v:adj[u])if(v!=par[u]){
            par[v]=u;
            dep[v]=dep[u]+1;
            dfs(v);
        }
    };
    for(int i=0;i<n+m;i++)if(i==fp(i))dfs(i);
    int q;
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(fp(u)!=fp(v)){
            cout << -1 << "\n";
            continue;
        }
        vector<int> a,b;
        while(dep[u]>dep[v]){
            a.emplace_back(u);
            u=par[u];
        }
        while(dep[v]>dep[u]){
            b.emplace_back(v);
            v=par[v];
        }
        while(u!=v){
            a.emplace_back(u);
            b.emplace_back(v);
            u=par[u],v=par[v];
        }
        a.emplace_back(u);
        reverse(b.begin(),b.end());
        a.insert(a.end(),b.begin(),b.end());
        cout << a.size()/2+1 << "\n";
        for(int i=0;i<a.size();i++){
            cout << a[i]-(i%2==1?m:0)+1 << " \n"[i==a.size()-1];
        }
    }
}