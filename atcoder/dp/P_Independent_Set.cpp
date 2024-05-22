#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const ll MOD=1e9+7;

int n;
vector<int> adj[N];
ll dp[N][2];

void dfs(int u,int p){
    dp[u][0]=dp[u][1]=1;
    for(auto v:adj[u])if(v!=p){
        dfs(v,u);
        dp[u][0]*=(dp[v][0]+dp[v][1]);
        dp[u][0]%=MOD;
        dp[u][1]*=dp[v][0];
        dp[u][1]%=MOD;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,0);
    cout << (dp[1][0]+dp[1][1])%MOD;
}