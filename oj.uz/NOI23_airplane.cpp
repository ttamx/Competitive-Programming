#include<bits/stdc++.h>
 
using namespace std;
 
using ll = long long;

const int N=2e5+5;
const int INF=INT_MAX/2;

int n,m;
int a[N];
vector<int> adj[N];
int dist1[N],dist2[N];
int ans=INF;

void dijkstra(int st,int *dist){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    for(int i=1;i<=n;i++)dist[i]=INF;
    dist[st]=0;
    pq.emplace(0,st);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto v:adj[u]){
            int nd=max(d+1,a[v]);
            if(nd<dist[v]){
                dist[v]=nd;
                pq.emplace(nd,v);
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dijkstra(1,dist1);
    dijkstra(n,dist2);
    for(int i=1;i<=n;i++){
        ans=min(ans,max(dist1[i],dist2[i])*2);
    }
    for(int u=1;u<=n;u++){
        for(auto v:adj[u]){
            ans=min(ans,max(dist1[u],dist2[v])*2+1);
        }
    }
    cout << ans;
}