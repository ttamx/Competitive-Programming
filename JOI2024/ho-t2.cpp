#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const ll INF=1e18;

int n,m,s,t,l;
ll k;
vector<pair<int,ll>> adj[N];
ll ds[N],dt[N];
vector<ll> v1,v2;
ll ans,cnt;

void dijk(ll *dist,int s){
    for(int i=1;i<=n;i++)dist[i]=INF;
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    dist[s]=0;
    pq.emplace(0,s);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:adj[u])if(d+w<dist[v]){
            dist[v]=d+w;
            pq.emplace(d+w,v);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    cin >> s >> t >> l >> k;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dijk(ds,s);
    if(ds[t]<=k)cout << 1LL*n*(n-1)/2,exit(0);
    dijk(dt,t);
    for(int i=1;i<=n;i++)v1.emplace_back(ds[i]);
    for(int i=1;i<=n;i++)v2.emplace_back(dt[i]);
    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());
    for(auto x:v1){
        while(!v2.empty()&&x+v2.back()+l>k)v2.pop_back();
        ans+=v2.size();
    }
    cout << ans;
}