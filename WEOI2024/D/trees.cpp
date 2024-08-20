#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int MOD=1e9+7;

int n;
vector<int> adj[N];
ll dp[N];
ll ans;

void dfs(int u,int p=-1){
    dp[u]=1;
    for(auto v:adj[u])if(v!=p){
        dfs(v,u);
        dp[u]*=dp[v];
        dp[u]%=MOD;
    }
    ans+=dp[u];
    ans%=MOD;
    dp[u]++;
    dp[u]%=MOD;
}

int count_sets(int _n, vector<int> _u, vector<int> _v){
    n=_n;
    for(int i=0;i<n-1;i++){
        int u=_u[i],v=_v[i];
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0);
    return ans;
}
