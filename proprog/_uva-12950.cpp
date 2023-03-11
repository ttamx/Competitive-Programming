#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    while(cin >> n >> m){
        vector<vector<pair<int,ll>>> adj(n+1);
        for(int i=0;i<m;i++){
            int u,v;
            ll w;
            cin >> u >> v >> w;
            adj[u].emplace_back(v,w);
            adj[v].emplace_back(u,w);
        }
        priority_queue<tuple<ll,int,int>,vector<tuple<ll,int,int>>,greater<tuple<ll,int,int>>> pq;
        vector<vector<ll>> dp(2,vector<ll>(n+1,1e18));
        pq.emplace(0,0,1);
        dp[0][1]=0;
        while(!pq.empty()){
            auto [d,b,u]=pq.top();
            pq.pop();
            for(auto [v,w]:adj[u]){
                if(d+w>=dp[b^1][v])continue;
                dp[b^1][v]=d+w;
                pq.emplace(d+w,b^1,v);
            }
        }
        cout << (dp[0][n]<1e18?dp[0][n]:-1) << '\n';
    }
}