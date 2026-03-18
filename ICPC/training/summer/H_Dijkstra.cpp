#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<ll> dist(n,INF);
    vector<int> par(n,-1);
    using P = pair<ll,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    pq.emplace(dist[0]=0,0);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:adj[u]){
            if(d+w<dist[v]){
                par[v]=u;
                pq.emplace(dist[v]=d+w,v);
            }
        }
    }
    if(par[n-1]==-1){
        cout << -1 << "\n";
        exit(0);
    }
    vector<int> ans;
    for(int u=n-1;u!=-1;u=par[u]){
        ans.emplace_back(u);
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}