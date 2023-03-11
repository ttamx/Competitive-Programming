#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;

int n,q,res;
bool ok=true;
int deg[N],sz[N],val[N];
bool vis[N];
vector<pair<int,int>> edge,adj[N];
vector<int> root;

void dfs(int u){
    vis[u]=true;
    if(deg[u]%2==1)sz[u]=1;
    for(auto [v,w]:adj[u]){
        if(vis[v]){
            if(val[v]!=(val[u]^w))ok=false;
            continue;
        }
        val[v]=(val[u]^w);
        dfs(v);
        sz[u]+=sz[v];
    }
}

void runcase(){
    cin >> n >> q;
    edge.resize(n-1);
    for(auto &[u,v]:edge){
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
    }
    for(int i=0;i<q;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    for(int i=1;i<=n;i++){
        if(vis[i])continue;
        root.push_back(i);
        dfs(i);
    }
    if(!ok){
        cout << "No\n";
        return;
    }
    for(int i=1;i<=n;i++)if(deg[i]%2==1)res^=val[i];
    for(auto i:root){
        if(sz[i]%2==0)continue;
        for(int i=1;i<=n;i++)vis[i]=false;
        vis[i]=true;
        stack<int> s;
        s.push(i);
        while(!s.empty()){
            int u=s.top();
            s.pop();
            vis[u]=true;
            val[u]^=res;
            for(auto [v,w]:adj[u]){
                if(vis[v])continue;
                vis[v]=true;
                s.push(v);
            }
        }
        break;
    }
    cout << "Yes\n";
    for(auto [u,v]:edge)cout << (val[u]^val[v]) << ' ';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}