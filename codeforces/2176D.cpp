#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<int>> adj(n);
    vector<map<ll,mint>> dp(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        dp[v][a[u]]++;
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return a[i]<a[j];
    });
    mint ans=0;
    for(auto u:ord){
        for(auto &[_,x]:dp[u]){
            ans+=x;
        }
        for(auto v:adj[u]){
            if(dp[u].count(a[v]-a[u])){
                dp[v][a[u]]+=dp[u][a[v]-a[u]];
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