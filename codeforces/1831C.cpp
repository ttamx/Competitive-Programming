#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<vector<pair<int,int>>> adj(n+1);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    vector<int> dp(n+1),val(n+1);
    val[1]=n;
    function<void(int,int)> dfs=[&](int u,int p){
        for(auto [v,w]:adj[u]){
            if(v==p)continue;
            val[v]=w;
            dfs(v,u);
            dp[u]=max(dp[u],dp[v]+(val[u]>w));
        }
    };
    dfs(1,0);
    cout << dp[1] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}