#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,int>;

const ll INF=1e18;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> st(k);
    for(auto &x:st)cin >> x;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<vector<ll>> dist(k,vector<ll>(n,INF));
    for(int i=0;i<k;i++){
        priority_queue<P,vector<P>,greater<P>> pq;
        auto go=[&](int u,ll d){
            if(d>=dist[i][u])return;
            dist[i][u]=d;
            pq.emplace(d,u);
        };
        go(st[i],0);
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(d>dist[i][u])continue;
            for(auto [v,w]:adj[u])go(v,d+w);
        }
    }
    ll ans=INF;
    vector<int> a(k);
    iota(a.begin(),a.end(),0);
    do{
        int u=0;
        ll res=0;
        for(int i=0;i<k;i++){
            res+=dist[a[i]][u];
            if(i==k-1)res+=dist[a[i]][0];
            u=st[a[i]];
        }
        ans=min(ans,res);
    }while(next_permutation(a.begin(),a.end()));
    cout << ans << "\n";
}