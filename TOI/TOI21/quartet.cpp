#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n+m);
    for(int i=0;i<n+m-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int ans=0;
    function<int(int,int)> dfs=[&](int u,int p){
        if(u<n)return 1;
        int s=0;
        array<int,5> dp{};
        dp[0]=1;
        for(auto v:adj[u])if(v!=p){
            int t=dfs(v,u);
            s+=t;
            for(int i=4;i>0;i--)dp[i]=(dp[i]+1LL*dp[i-1]*t)%MOD;
        }
        for(int i=4;i>0;i--)dp[i]=(dp[i]+1LL*dp[i-1]*(n-s))%MOD;
        ans=(ans+dp[4])%MOD;
        return s;
    };
    dfs(n,-1);
    cout << ans << "\n";
}