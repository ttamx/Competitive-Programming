#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    vector<mint> dp(n);
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        x--;
        a[x]=1;
        dp[x]=1;
    }
    vector<pair<int,int>> e(n-1);
    vector<vector<int>> adj(n);
    for(auto &[u,v]:e){
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> par(n,-1);
    function<void(int)> dfs=[&](int u){
        for(int v:adj[u])if(v!=par[u]){
            par[v]=u;
            dfs(v);
            a[u]+=a[v];
        }
    };
    dfs(0);
    mint ans=0;
    for(auto [u,v]:e){
        if(u!=par[v])swap(u,v);
        mint p=dp[u],q=dp[v];
        mint su=k-a[v],sv=a[v];
        mint uv=p*(1-q)/2;
        mint vu=q*(1-p)/2;
        ans+=su*sv*(1-uv-vu);
        ans+=(su-1)*(sv+1)*uv;
        ans+=(su+1)*(sv-1)*vu;
        dp[u]=p*(1-(1-q)/2)+(1-p)*q/2;
        dp[v]=q*(1-(1-p)/2)+(1-q)*p/2;
    }
    ans/=1LL*k*(k-1)/2;
    cout << ans;
}