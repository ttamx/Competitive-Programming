#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD=998244353;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<array<ll,2>> dp(n);
    function<void(int,int)> dfs=[&](int u,int p){
        dp[u]={1,0};
        int ch=0;
        ll c=0;
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            ll w=(dp[v][0]+dp[v][1])%MOD;
            dp[u][1]=(dp[u][1]*w+dp[u][0]*dp[v][1])%MOD;
            dp[u][0]=dp[u][0]*w%MOD;
            ch++;
        }
        if(ch==0){
            dp[u][1]=1;
        }
    };
    dfs(0,-1);
    cout << dp[0][0] << "\n";
}