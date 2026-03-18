#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,int>;

const int N=1e5+5;
const ll INF=1e18;

int n,m,k;
vector<tuple<int,int,int>> edges;
vector<tuple<ll,int,int>> edges2;
vector<pair<int,int>> adj[N];
int src[N];
ll dist[N];
priority_queue<P,vector<P>,greater<P>> pq;
int fa[N];
ll ans;

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    edges.resize(m);
    for(auto &[u,v,w]:edges){
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    for(int i=1;i<=n;i++)dist[i]=INF;
    cin >> k;
    while(k--){
        int x;
        cin >> x;
        src[x]=x;
        pq.emplace(dist[x]=0,x);
    }
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:adj[u])if(d+w<dist[v])pq.emplace(dist[v]=d+w,v),src[v]=src[u];
    }
    ans=dist[1];
    for(auto [u,v,w]:edges)if(src[u]!=src[v])edges2.emplace_back(dist[u]+dist[v]+w,src[u],src[v]);
    sort(edges2.begin(),edges2.end());
    for(int i=1;i<=n;i++)fa[i]=i;
    for(auto [w,u,v]:edges2){
        u=fp(u),v=fp(v);
        if(u!=v)ans+=w,fa[v]=u;
    }
    cout << ans << "\n";
}