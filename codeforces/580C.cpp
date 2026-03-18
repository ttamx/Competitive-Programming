#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int ans=0;
    function<void(int,int,int,int)> dfs=[&](int u,int p,int mx,int suf){
        suf=(suf+a[u])*a[u];
        mx=max(mx,suf);
        int ch=0;
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u,mx,suf);
            ch++;
        }
        if(!ch&&mx<=m){
            ans++;
        }
    };
    dfs(0,-1,0,0);
    cout << ans << "\n";
}