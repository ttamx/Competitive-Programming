#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n+1);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dp(n+1,n);
    int ans=0;
    function<void(int,int,int)> dfs=[&](int u,int p,int l){
        dp[u]=min(dp[u],l);
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u,dp[u]+1);
            if(dp[v]>2){
                dp[u]=min(dp[u],1);
                dp[p]=min(dp[p],2);
                ans++;
            }
        }
    };
    dfs(1,1,0);
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}