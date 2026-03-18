#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

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
    vector<int> a(n),b(k);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    vector<int> val(1<<k);
    for(int mask=0;mask<1<<k;mask++){
        for(int i=0;i<k;i++){
            if(mask>>i&1){
                val[mask]^=b[i];
            }
        }
    }
    vector<int> sum(n);
    vector<vector<mint>> dp(n,vector<mint>(1<<k));
    function<void(int,int)> dfs=[&](int u,int p){
        sum[u]=a[u];
        dp[u][0]=1;
        for(auto v:adj[u])if(v!=p){
            dfs(v,u);
            sum[u]^=sum[v];
            vector<mint> ndp(1<<k);
            for(int i=0;i<1<<k;i++){
                for(int j=0;j<1<<k;j++){
                    ndp[i^j]+=dp[u][i]*dp[v][j];
                }
            }
            dp[u]=move(ndp);
        }
        if(u==0)return;
        auto tmp=dp[u];
        for(int mask=0;mask<1<<k;mask++){
            int cur=sum[u]^val[mask];
            for(int i=0;i<k;i++){
                if(cur==b[i]){
                    dp[u][mask^(1<<i)]+=tmp[mask];
                }
            }
        }
    };
    dfs(0,-1);
    mint ans=0;
    for(int mask=0;mask<1<<k;mask++){
        int cur=sum[0]^val[mask];
        for(int i=0;i<k;i++){
            if(cur==b[i]){
                ans+=dp[0][mask];
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}