#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<mint> p(n);
    for(auto &x:p){
        mint a,b;
        cin >> a >> b;
        x=a/b;
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> par(n,-1);
    vector<mint> dp(n);
    mint ans=0;
    function<void(int)> dfs=[&](int u){
        mint prob=(par[u]==-1?1:p[par[u]])*(1-p[u]);
        for(auto v:adj[u]){
            if(v==par[u])continue;
            dfs(v);
            prob*=p[v];
        }
        for(auto v:adj[u]){
            if(v==par[u])continue;
            
        }
    };
    dfs(0);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}