#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const ll INF=LLONG_MAX/2;

int n,m,a,b,c,d;
vector<pair<int,int>> adj[N];
bool ban[N];
ll dist[3][N];

void dijk(int st,ll *dist){
    for(int i=1;i<=n;i++)dist[i]=INF;
    using P = pair<ll,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    dist[st]=0;
    pq.emplace(0,st);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:adj[u])if(!ban[v]&&d+w<dist[v]){
            dist[v]=d+w;
            pq.emplace(dist[v],v);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    cin >> a >> b >> c >> d;
    dijk(a,dist[0]);
    dijk(b,dist[1]);
    ll sp=dist[0][b];
    for(int i=1;i<=n;i++)ban[i]=dist[0][i]+dist[1][i]==sp;
    dijk(c,dist[2]);
    cout << (dist[2][d]==INF?-1:dist[2][d]);
}