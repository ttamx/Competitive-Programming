#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int,int>> edges(m);
    vector<vector<int>> adj(n);
    vector<int> deg(n);
    for(int i=0;i<m;i++){
        auto &[u,v,r,p]=edges[i];
        cin >> u >> v >> r >> p;
        u--,v--;
        adj[v].emplace_back(i);
        deg[u]++;
    }
    vector<int> ans(n,-1);
    vector<bool> vis(m);
    queue<int> q;
    for(int i=0;i<n;i++){
        if(deg[i]==0){
            q.emplace(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto i:adj[u]){
            vis[i]=true;
            int v=get<0>(edges[i]);
            if(--deg[v]==0){
                q.emplace(v);
            }
        }
    }
    priority_queue<pair<int,int>> pq;
    for(int i=0;i<m;i++){
        if(!vis[i]){
            pq.emplace(get<2>(edges[i]),i);
        }
    }
    while(!pq.empty()){
        auto [d,i]=pq.top();
        pq.pop();
        if(vis[i])continue;
        vis[i]=true;
        int u=get<0>(edges[i]);
        if(--deg[u]==0){
            ans[u]=d;
            for(auto j:adj[u]){
                auto [v,_,r,p]=edges[j];
                if(!vis[j]&&d-p>r){
                    pq.emplace(d-p,j);
                }
            }
        }
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}