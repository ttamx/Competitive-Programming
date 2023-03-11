#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> sz(m),t(m);
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){
        cin >> sz[i];
        for(int j=0;j<sz[i];j++){
            int x;
            cin >> x;
            adj[x].push_back(i);
        }
        cin >> t[i];
    }
    int ans=0;
    vector<bool> vis(n);
    function<void(int)> dfs=[&](int u){
        if(vis[u])return;
        vis[u]=true;
        ans++;
        for(auto v:adj[u]){
            sz[v]--;
            if(sz[v]==0)dfs(t[v]);
        }
    };
    dfs(1);
    cout << ans;
}