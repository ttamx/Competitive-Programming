#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const ll INF=LLONG_MAX/2;

int n,m;
vector<pair<int,int>> adj[N];
ll dist[N];
bool vis[N];
using P = pair<ll,int>;
priority_queue<P,vector<P>,greater<P>> pq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
    }
    for(int i=1;i<=n;i++)dist[i]=INF;
    dist[1]=0;
    pq.push({dist[1],1});
    while(!pq.empty()){
        // ll d=pq.top().first;
        // int u=pq.top().second;
        auto [d,u]=pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(auto [v,w]:adj[u]){
            if(d+w<dist[v]){
                dist[v]=d+w;
                pq.push({dist[v],v});
            }
        }
    }
    for(int i=1;i<=n;i++)cout << dist[i] << " \n"[i==n];
}