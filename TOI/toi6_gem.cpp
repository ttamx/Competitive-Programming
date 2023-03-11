#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> a(n);
    for(auto &[u,v]:a)cin >> u >> v;
    vector<int> neg(m+1);
    for(int i=0;i<m;i+=2){
        int u,v;
        cin >> u >> v;
        neg[u]=v;
        neg[v]=u;
    }
    vector<vector<int>> adj(m+1),rev(m+1);
    for(auto [u,v]:a){
        adj[neg[u]].emplace_back(v);
        adj[neg[v]].emplace_back(u);
        rev[v].emplace_back(neg[u]);
        rev[u].emplace_back(neg[v]);
    }
    vector<bool> vis(m+1);
    stack<int> s;
    function<void(int)> dfs=[&](int u){
        if(vis[u])return;
        vis[u]=true;
        for(auto v:adj[u])dfs(v);
        s.emplace(u);
    };
    for(int i=1;i<=m;i++)dfs(i);
    fill(vis.begin(),vis.end(),false);
    vector<int> si(m+1),sz(m+1);
    function<void(int,int)> scc=[&](int u,int i){
        if(vis[u])return;
        vis[u]=true;
        si[u]=i;
        for(auto v:rev[u])scc(v,i);
    };
    while(!s.empty()){
        scc(s.top(),s.top());
        s.pop();
    }
    char ans='Y';
    for(int i=1;i<=m;i++)if(si[i]==si[neg[i]])ans='N';
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(5);
    while(t--)solve();
}