#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    priority_queue<int,vector<int>,greater<int>> pq;
    vector<bool> vis(n);
    vis[0]=true;
    pq.emplace(0);
    while(!pq.empty()){
        int u=pq.top();
        pq.pop();
        cout << u+1 << " ";
        for(auto v:adj[u]){
            if(!vis[v]){
                vis[v]=true;
                pq.emplace(v);
            }
        }
    }
    cout << "\n";
}