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
    vector<int> sz(n);
    vector<mint> dp(n),dp2(n),dp3(n),dp4(n),dp5(n);
    function<bool(int,int)> dfs=[&](int u,int p){
        bool c=(u==n-1);
        int idx=-1;
        sz[u]=1;
        dp4[u]=1;
        dp5[u]=0;
        mint tot=0;
        for(auto v:adj[u])if(v!=p){
            if(dfs(v,u)){
                c=true;
                idx=v;
            }else{
                sz[u]+=sz[v];
                dp4[u]+=2*tot*dp4[v];
                dp4[u]+=dp4[v];
                dp4[u]+=2*dp5[v]+1;
                dp5[u]+=dp4[v];
                tot+=dp4[v];
            }
        }
        if(c){
            if(u==n-1){
                dp[u]=1;
                dp2[u]=0;
                dp3[u]=0;
                dp4[u]=1;
                dp5[u]=0;
            }else{
                dp[u]=dp[idx]*dp4[u]+dp2[idx]*(dp5[u]*2+1)+dp3[idx];
                dp2[u]=dp2[idx]*2+dp[idx]*(dp5[u]*2+1);
                dp3[u]=dp[idx];
            }
        }
        return c;
    };
    dfs(0,-1);
    cout << dp[0] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}