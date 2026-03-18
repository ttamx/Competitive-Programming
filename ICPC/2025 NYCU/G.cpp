#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q;
    cin >> n >> m >> q;
    vector<vector<pair<int,double>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,e;
        cin >> u >> v >> e;
        u--,v--;
        adj[u].emplace_back(v,e*0.01);
    }
    cout << fixed << setprecision(15);
    while(q--){
        int s,t,x;
        cin >> s >> t >> x;
        s--,t--;
        priority_queue<pair<double,int>> pq;
        vector<double> dp(n);
        vector<bool> vis(n);
        pq.emplace(dp[s]=x,s);
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(vis[u])continue;
            vis[u]=true;
            for(auto [v,e]:adj[u]){
                double nd=d*e;
                if(nd>dp[v]){
                    pq.emplace(dp[v]=nd,v);
                }
            }
        }
        cout << dp[t] << "\n";
    }
}