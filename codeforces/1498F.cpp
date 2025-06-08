#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
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
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<int>> dp(n,vector<int>(2*k));
    vector<vector<int>> up(n,vector<int>(2*k));
    function<void(int,int)> dfs=[&](int u,int p){
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            for(int i=0;i<2*k;i++){
                dp[u][i]^=dp[v][i];
            }
        }
        rotate(dp[u].begin(),dp[u].end()-1,dp[u].end());
        dp[u][0]^=a[u];
    };
    function<void(int,int)> dfs2=[&](int u,int p){
        dp[u][0]=a[u];
        for(int t=0;t<2;t++){
            vector<int> cur(2*k);
            for(auto v:adj[u]){
                if(v==p)continue;
                for(int i=0;i<2*k;i++){
                    up[v][i]^=cur[i];
                }
                for(int i=0;i<2*k;i++){
                    cur[i]^=dp[v][i];
                }
            }
            reverse(adj[u].begin(),adj[u].end());
        }
        for(auto v:adj[u]){
            if(v==p)continue;
            for(int i=0;i<2*k;i++){
                up[v][i]^=up[u][i];
            }
            rotate(up[v].begin(),up[v].end()-1,up[v].end());
            up[v][0]^=a[u];
            dfs2(v,u);
        }
        rotate(up[u].begin(),up[u].end()-1,up[u].end());
        for(int i=0;i<2*k;i++){
            dp[u][i]^=up[u][i];
        }
    };
    dfs(0,-1);
    dfs2(0,-1);
    for(int u=0;u<n;u++){
        int sum=0;
        for(int i=k;i<2*k;i++){
            sum^=dp[u][i];
        }
        cout << (sum>0) << " \n"[u==n-1];
    }
}