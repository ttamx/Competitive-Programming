#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<tuple<int,int,int>>> adj(n);
    vector<int> bal(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w,-1);
        adj[v].emplace_back(u,w,i);
        bal[u]+=w;
        bal[v]+=w;
    }
    for(int i=1;i<n-1;i++){
        bal[i]/=2;
    }
    queue<int> q;
    vector<bool> vis(n);
    vis[0]=true;
    q.emplace(0);
    vector<int> ans(m);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto [v,w,i]:adj[u]){
            if(!vis[v]){
                if(i!=-1){
                    ans[i]=1;
                }
                bal[v]-=w;
                if(bal[v]==0){
                    vis[v]=true;
                    q.emplace(v);
                }
            }   
        }
    }
    for(auto x:ans){
        cout << x << "\n";
    }
}