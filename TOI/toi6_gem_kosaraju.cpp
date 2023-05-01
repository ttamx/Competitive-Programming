#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> a(n);
    for(auto &[u,v]:a)cin >> u >> v;
    vector<vector<int>> adj(m+1),rev(m+1);
    vector<int> neg(m+1);
    for(int i=0;i<m;i+=2){
        int u,v;
        cin >> u >> v;
        neg[u]=v;
        neg[v]=u;
    }
    for(auto &[u,v]:a){
        adj[neg[u]].emplace_back(v);
        adj[neg[v]].emplace_back(u);
        rev[v].emplace_back(neg[u]);
        rev[u].emplace_back(neg[v]);
    }
    vector<bool> vis(m+1);
    vector<int> scc(m+1);
    stack<int> s;
    function<void(int)> dfs=[&](int u){
        if(vis[u])return;
        vis[u]=true;
        for(auto &v:adj[u])dfs(v);
        s.emplace(u);
    };
    for(int i=1;i<=m;i++)dfs(i);
    fill(vis.begin(),vis.end(),false);
    function<void(int,int)> dfs2=[&](int u,int rt){
        if(vis[u])return;
        vis[u]=true;
        scc[u]=rt;
        for(auto &v:rev[u])dfs2(v,rt);
    };
    while(!s.empty()){
        int rt=s.top();
        s.pop();
        dfs2(rt,rt);
    }
    for(int i=1;i<=m;i++)if(scc[i]==scc[neg[i]])return void(cout << "N");
    cout << "Y";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(5);
    while(t--)runcase();
}