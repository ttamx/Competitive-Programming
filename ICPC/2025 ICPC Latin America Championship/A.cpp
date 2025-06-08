#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<pair<int,char>>> adj(n),rev(n);
    vector<vector<bool>> vis(n,vector<bool>(n));
    queue<pair<int,int>> q;
    for(int i=0;i<n;i++){
        vis[i][i]=true;
        q.emplace(i,i);
    }
    for(int i=0;i<m;i++){
        int u,v;
        char c;
        cin >> u >> v >> c; 
        u--,v--;
        adj[u].emplace_back(v,c);
        rev[v].emplace_back(u,c);
        if(!vis[u][v]){
            vis[u][v]=true;
            q.emplace(u,v);
        }
    }
    int ans=0;
    while(!q.empty()){
        auto [u,v]=q.front();
        q.pop();
        if(u!=v)ans++;
        for(auto [uu,cu]:rev[u]){
            for(auto [vv,cv]:adj[v]){
                if(cu==cv&&!vis[uu][vv]){
                    vis[uu][vv]=true;
                    q.emplace(uu,vv);
                }
            }
        }
    }
    cout << ans << "\n";
}