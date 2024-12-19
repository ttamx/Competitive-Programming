#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
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
    vector<array<mint,3>> dp(n);
    function<void(int u,int p)> dfs=[&](int u,int p){
        mint pw=1;
        mint all=1;
        dp[u][1]=dp[u][2]=1;
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            all*=(dp[v][0]*2+dp[v][2]);
            dp[u][1]*=dp[v][0]*2+dp[v][2];
            dp[u][2]*=dp[v][0]+dp[v][2];
        }
        dp[u][0]=0;
        for(auto v:adj[u]){
            if(v==p)continue;
            dp[u][0]+=dp[v][1]*all/(dp[v][0]*2+dp[v][2]);
        }
    };
    dfs(0,-1);
    cout << dp[0][0]+dp[0][2] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}