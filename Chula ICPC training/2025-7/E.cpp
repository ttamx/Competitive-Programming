#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,mod;
    cin >> n >> mod;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<ll> dp(n),up(n),pre(n),suf(n);
    function<void(int,int)> dfs=[&](int u,int p){
        dp[u]=1;
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            dp[u]=dp[u]*(1+dp[v])%mod;
        }
    };
    function<void(int,int)> dfs2=[&](int u,int p){
        for(int t=0;t<2;t++){
            ll cur=1;
            for(auto v:adj[u]){
                if(v==p)continue;
                (t?suf:pre)[v]=cur;
                cur=cur*(dp[v]+1)%mod;
            }
            reverse(adj[u].begin(),adj[u].end());
        }
        for(auto v:adj[u]){
            if(v==p)continue;
            up[v]=pre[v]*suf[v]%mod*(up[u]+1)%mod;
            dfs2(v,u);
        }
    };
    dfs(0,-1);
    dfs2(0,-1);
    for(int i=0;i<n;i++){
        cout << dp[i]*(up[i]+1)%mod << "\n";
    }
}