#include<bits/stdc++.h>

using namespace std;

void runcase(){
    cerr << '\n';
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n+1);
    vector<int> deg(n+1);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<bool> vis(n+1);
    int k=-1;
    queue<int> q;
    for(int i=1;i<=n;i++)if(deg[i]==2)q.emplace(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(vis[u])continue;
        vis[u]=true;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}