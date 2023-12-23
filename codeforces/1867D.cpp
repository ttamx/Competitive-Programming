#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    bool ans=true;
    vector<vector<int>> adj(n+2);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        adj[i].emplace_back(x);
        if(k==1&&x!=i)ans=false;
    }
    vector<int> vis(n+2),dist(n+2);
    function<void(int)> dfs=[&](int u){
        vis[u]=1;
        for(auto v:adj[u]){
            if(vis[v]==2)continue;
            if(vis[v]==1){
                if(dist[u]-dist[v]+1!=k)ans=false;
                continue;
            }
            dist[v]=dist[u]+1;
            dfs(v);
        }
        vis[u]=2;
    };
    for(int i=1;i<=n;i++)if(!vis[i])dfs(i);
    cout << (ans?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}