#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    n++;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    vector<int> par(n),jump(n),dep(n);
    function<void(int)> dfs=[&](int u){
        for(auto v:adj[u]){
            dep[v]=dep[u]+1;
            par[v]=u;
            jump[v]=(dep[u]-dep[jump[u]]==dep[jump[u]]-dep[jump[jump[u]]])?jump[jump[u]]:u;
            dfs(v);
        }
    };
    dfs(0);
    auto lift=[&](int u,int d){
        while(dep[u]>d)u=(dep[jump[u]]>=d?jump[u]:par[u]);
        return u;
    };
    int q;
    cin >> q;
    vector<int> ans(q);
    vector<vector<pair<int,int>>> qr(n);
    for(int i=0;i<q;i++){
        int u,x;
        cin >> u >> x;
        if(x<dep[u]){
            qr[lift(u,dep[u]-x)].emplace_back(dep[u],i);
        }
    }
    vector<map<int,int>> ds(n);
    function<void(int)> dfs2=[&](int u){
        ds[u][dep[u]]++;
        for(auto v:adj[u]){
            dfs2(v);
            if(ds[v].size()>ds[u].size())swap(ds[u],ds[v]);
            for(auto [x,c]:ds[v])ds[u][x]+=c;
        }
        for(auto [d,i]:qr[u]){
            ans[i]=ds[u][d]-1;
        }
    };
    dfs2(0);
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}