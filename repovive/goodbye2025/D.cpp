#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(u<v)swap(u,v);
        adj[u].emplace_back(v);
    }
    for(auto &v:adj){
        sort(v.rbegin(),v.rend());
    }
    vector<mint> dp(n);
    dp[n-1]=1;
    for(int u=n-1;u>=1;u--){
        vector<mint> ndp(n);
        auto aux=dp;
        for(int i=1;i<n;i++){
            aux[i]+=aux[i-1];
        }
        mint ways=1;
        for(auto v:adj[u]){
            ndp[v]+=ways*(aux[v]+dp[u]);
            ways*=2;
        }
        dp=move(ndp);
    }
    cout << dp[0] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}