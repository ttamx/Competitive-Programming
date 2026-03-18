#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> par(n,-1);
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        cin >> par[i];
        par[i]--;
        adj[par[i]].emplace_back(i);
    }
    int buf=0;
    vector<int> id(n,-1);
    for(int u=n-1;u!=-1;u=par[u]){
        id[u]=buf++;
    }
    vector<mint> pw(n+1);
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*2;
    }
    mint ans=(buf-1)*pw[n];
    function<int(int)> dfs=[&](int u){
        int s=1;
        for(auto v:adj[u]){
            int t=dfs(v);
            if(id[v]==-1){
                ans+=(pw[t]-1)*pw[n-t];
            }
            s+=t;
        }
        return s;
    };
    dfs(0);
    function<int(int)> find=[&](int u){
        if(id[u]!=-1)return id[u];
        return id[u]=find(par[u]);
    };
    vector<int> cnt(buf);
    for(int i=0;i<n;i++){
        cnt[find(i)]++;
    }
    mint pre=0;
    for(int k=1;k<buf;k++){
        vector<mint> dp(buf);
        dp[0]=pw[cnt[0]];
        mint sum=dp[0];
        for(int i=1;i<buf;i++){
            if(i>k){
                sum-=dp[i-k-1];
            }
            dp[i]=sum*(pw[cnt[i]]-(i<buf-1));
            sum+=dp[i];
        }
        ans-=(dp[buf-1]-pre)*k;
        pre=dp[buf-1];
    }
    cout << ans*2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}