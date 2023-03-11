#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<int>> dp(n,vector<int>(n,-1));
    vector<vector<int>> pa(n,vector<int>(n,0));
    vector<vector<int>> adj(n);
    for(int i=1,u,v;i<n;i++){
        cin >> u >> v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    function<void(int,int,int)> dfs=[&](int u,int p,int r){
        pa[u][r]=p;
        for(auto v:adj[u])if(v!=p)dfs(v,u,r);
    };
    function<int(int,int)> calc=[&](int u,int v){
        if(dp[u][v]!=-1)return dp[u][v];
        dp[u][v]=0;
        if(u==v)return dp[u][v]=1;
        dp[u][v]=max({dp[u][v],calc(pa[u][v],v),calc(u,pa[v][u])});
        if(s[u]==s[v]){
            if(pa[u][v]==v)dp[u][v]=max(dp[u][v],2);
            else dp[u][v]=max(dp[u][v],2+calc(pa[u][v],pa[v][u]));
        }
        return dp[u][v];
    };
    int ans=0;
    for(int i=0;i<n;i++)dfs(i,i,i);
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)ans=max(ans,calc(i,j));
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}