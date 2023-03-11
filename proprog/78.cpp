#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    while(cin >> n >> m){
        vector<vector<pair<int,ll>>> adj(n);
        for(int i=0;i<m;i++){
            int u,v;
            ll w;
            cin >> u >> v >> w;
            adj[u].emplace_back(v,w);
            adj[v].emplace_back(u,w);
        }
        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
        vector<vector<ll>> dp(2,vector<ll>(n,1e18));
        for(int i=0;i<2;i++){
            vector<bool> vis(n);
            pq.emplace(0,i*(n-1));
            dp[i][i*(n-1)]=0;
            while(!pq.empty()){
                auto [d,u]=pq.top();
                pq.pop();
                if(vis[u])continue;
                vis[u]=true;
                for(auto [v,w]:adj[u]){
                    if(d+w<dp[i][v]){
                        dp[i][v]=d+w;
                        pq.emplace(d+w,v);
                    }
                }
            }
        }
        ll ans=0;
        for(int u=0;u<n;u++)for(auto [v,w]:adj[u])if(dp[0][u]+dp[1][v]+w==dp[0][n-1])ans+=w;
        cout << ans*2 << '\n';
    }
}