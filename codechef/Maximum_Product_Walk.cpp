#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    ll cur=*max_element(a.begin(),a.end());
    vector<array<ll,2>> dp(n);
    function<void(int,int)> dfs=[&](int u,int p){
        dp[u]={-LINF,-LINF};
        dp[u][a[u]<0]=abs(a[u]);
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            auto tmp=dp[u];
            for(int i=0;i<2;i++){
                if(dp[v][i]<0)continue;
                for(int j=0;j<2;j++){
                    dp[u][j]=max(dp[u][j],tmp[i^j]+dp[v][i]);
                }
            }
        }
        if(dp[u][0]>0){
            cur=max(cur,dp[u][0]);
        }
    };
    dfs(0,-1);
    mint ans=1;
    if(cur<0){
        cur=-cur;
        ans=-1;
    }
    mint mul=2;
    while(cur>0){
        if(cur&1)ans*=mul;
        mul*=mul;
        cur>>=1;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}