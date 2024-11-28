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
    vector<mint> ans(n);
    vector<int> dp(n,INF),nxt(n,-1),par(n,-1);
    vector<int> ord;
    function<void(int)> dfs=[&](int u){
        ord.emplace_back(u);
        int ch=0;
        for(auto v:adj[u]){
            if(v==par[u])continue;
            ch++;
            par[v]=u;
            dfs(v);
            if(dp[v]+1<dp[u]){
                dp[u]=dp[v]+1;
                nxt[u]=v;
            }
        }
        if(ch==0){
            dp[u]=0;
        }
    };
    dfs(0);
    vector<bool> vis(n);
    ans[0]=1;
    vis[0]=true;
    for(auto u:ord){
        if(vis[u])continue;
        vector<int> a;
        for(int v=u;v!=-1;v=nxt[v]){
            a.emplace_back(v);
            vis[v]=true;
        }
        int len=a.size();
        mint base=ans[par[u]]/len;
        reverse(a.begin(),a.end());
        for(int i=0;i<a.size();i++){
            ans[a[i]]=base*i;
        }
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}