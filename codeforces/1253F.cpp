#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,int>;

const int N=1e5+5;
const int M=3e5+5;
const int Q=3e5+5;
const ll INF=1e18;

int n,m,k,q;
vector<tuple<int,int,int>> edges;
vector<tuple<ll,int,int>> edges2;
vector<pair<int,int>> adj[N];
int src[N];
ll dist[N];
priority_queue<P,vector<P>,greater<P>> pq;
int st[Q],ed[Q],l[Q],r[Q];
vector<int> check[M];
int fa[N];

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k >> q;
    edges.resize(m);
    for(auto &[u,v,w]:edges){
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    for(int i=1;i<=k;i++)src[i]=i,pq.emplace(0,i);
    for(int i=k+1;i<=n;i++)dist[i]=INF;
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:adj[u])if(d+w<dist[v])pq.emplace(dist[v]=d+w,v),src[v]=src[u];
    }
    for(auto [u,v,w]:edges)if(src[u]!=src[v])edges2.emplace_back(dist[u]+dist[v]+w,src[u],src[v]);
    sort(edges2.begin(),edges2.end());
    m=edges2.size();
    for(int i=1;i<=q;i++){
        cin >> st[i] >> ed[i];
        l[i]=0,r[i]=m-1;
    }
    while(true){
        bool done=true;
        for(int i=1;i<=q;i++)if(l[i]<r[i])check[(l[i]+r[i])/2].emplace_back(i),done=false;
        if(done)break;
        for(int i=1;i<=k;i++)fa[i]=i;
        for(int i=0;i<m;i++){
            auto [w,u,v]=edges2[i];
            fa[fp(u)]=fp(v);
            for(auto j:check[i]){
                if(fp(st[j])==fp(ed[j]))r[j]=i;
                else l[j]=i+1;
            }
            vector<int>().swap(check[i]);
        }
    }
    for(int i=1;i<=q;i++)cout << get<0>(edges2[l[i]]) << "\n";
}