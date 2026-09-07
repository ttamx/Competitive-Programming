#include<bits/stdc++.h>

using namespace std;

void no(){
    cout << "NO\n";
    exit(0);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,s;
    cin >> n >> m >> s;
    s--;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
    }
    vector<int> d(n),vis(n);
    for(auto &x:d)cin >> x;
    for(int u=0;u<n;u++){
        if(d[u]==-1)continue;
        for(auto [v,w]:adj[u]){
            if(d[v]==-1||d[v]>d[u]+w)no();
        }
    }
    queue<int> q;
    q.emplace(s);
    if(d[s])no();
    vis[s]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto [v,w]:adj[u]){
            if(!vis[v]&&d[u]+w==d[v]){
                vis[v]=1;
                q.emplace(v);
            }
        }
    }
    for(int i=0;i<n;i++){
        if((vis[i]==1)!=(d[i]!=-1))no();
    }
    cout << "YES\n";
}