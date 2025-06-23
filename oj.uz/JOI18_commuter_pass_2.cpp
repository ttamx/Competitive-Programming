#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const ll INF=LLONG_MAX/2;

int n,m,S,T,U,V;
vector<pair<int,int>> adj[N];
vector<int> adj2[N];
ll distS[N],distU[N],distV[N];
ll dp[N][2][2];

void dijkstra(ll *dist,int s){
    using P = pair<ll,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    for(int i=1;i<=n;i++){
        dist[i]=INF;
    }
    dist[s]=0;
    pq.emplace(0,s);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        for(auto [v,w]:adj[u]){
            if(d+w<dist[v]){
                dist[v]=d+w;
                pq.emplace(dist[v],v);
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> S >> T >> U >> V;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dijkstra(distS,S);
    dijkstra(distU,U);
    dijkstra(distV,V);
    for(int u=1;u<=n;u++){
        for(auto [v,w]:adj[u]){
            if(distS[v]+w==distS[u]){
                adj2[u].emplace_back(v);
            }
        }
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return distS[i]<distS[j];
    });
    for(int i=1;i<=n;i++){
        for(int x=0;x<2;x++){
            for(int y=0;y<2;y++){
                dp[i][x][y]=INF;
            }
        }
    }
    dp[S][0][0]=0;
    for(auto u:ord){
        for(auto v:adj2[u]){
            for(int x=0;x<2;x++){
                for(int y=0;y<2;y++){
                    dp[u][x][y]=min(dp[u][x][y],dp[v][x][y]);
                }
            }
        }
        dp[u][0][1]=min(dp[u][0][1],dp[u][0][0]+distU[u]);
        dp[u][1][0]=min(dp[u][1][0],dp[u][0][0]+distV[u]);
        dp[u][1][1]=min({dp[u][1][1],dp[u][1][0]+distU[u],dp[u][0][1]+distV[u]});
    }
    cout << min(dp[T][1][1],distU[V]) << "\n";
}