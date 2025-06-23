#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    mint ans=0;
    vector<int> sz(n);
    function<void(int,int)> dfs=[&](int u,int p){
        vector<int> s;
        sz[u]=1;
        for(auto v:adj[u])if(v!=p){
            dfs(v,u);
            sz[u]+=sz[v];
            s.emplace_back(sz[v]);
        }
        if(sz[u]<n)s.emplace_back(n-sz[u]);
        mint bad=0;
        for(auto x:s)bad+=comb.C(x,k);
        ans+=(comb.C(n,k)-bad)*n;
        for(auto x:s){
            ans+=x*(comb.C(n-x,k)-bad+comb.C(x,k))*(n-x);
        }
    };
    dfs(0,-1);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}