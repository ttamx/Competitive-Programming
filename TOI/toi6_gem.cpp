#include<bits/stdc++.h>

using namespace std;

const int N=4e5+5;

vector<int> adj[N];
int disc[N],low[N],scc[N];
int timer;
stack<int> s;

void dfs(int u){
    disc[u]=low[u]=++timer;
    s.emplace(u);
    for(int v:adj[u]){
        if(!disc[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }else if(!scc[v]){
            low[u]=min(low[u],disc[v]);
        }
    }
    if(disc[u]==low[u]){
        int t;
        do{
            t=s.top();
            s.pop();
            scc[t]=u;
        }while(t!=u);
    }
}

void solve(){
    int n,m;
    cin >> n >> m;
    for(int i=0;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u+m].emplace_back(v);
        adj[v+m].emplace_back(u);
    }
    for(int i=0;i<m;i+=2){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v+m);
        adj[v].emplace_back(u+m);
    }
    timer=0;
    for(int i=1;i<=2*m;i++)if(!disc[i])dfs(i);
    bool ok=true;
    for(int i=1;i<=m;i++)if(scc[i]==scc[i+m]){
        ok=false;
        break;
    }
    cout << "NY"[ok];
    for(int i=1;i<=2*m;i++){
        adj[i].clear();
        disc[i]=low[i]=scc[i]=0;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(5);
    while(t--)solve();
}