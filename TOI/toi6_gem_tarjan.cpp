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
    vector<vector<int>> adj(m+1);
    for(auto [u,v]:a){
        adj[neg[u]].emplace_back(v);
        adj[neg[v]].emplace_back(u);
    }
    vector<int> disc(m+1),low(m+1),scc(m+1);
    vector<bool> inpath(m+1);
    stack<int> path;
    int idx=0;
    function<void(int)> tarjan=[&](int u){
        disc[u]=low[u]=++idx;
        path.emplace(u);
        inpath[u]=true;
        for(auto v:adj[u]){
            if(!disc[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(inpath[v]){
                low[u]=min(low[u],low[v]);
            }
        }
        if(low[u]==disc[u]){
            int t;
            do{
                t=path.top();
                path.pop();
                inpath[t]=false;
                scc[t]=u;
            }while(t!=u);
        }
    };
    for(int i=1;i<=m;i++)if(!disc[i])tarjan(i);
    char ans='Y';
    for(int i=1;i<=m;i++)if(scc[i]==scc[neg[i]])ans='N';
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(5);
    while(t--)solve();
}