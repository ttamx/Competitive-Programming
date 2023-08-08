#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;

const int N=1e5+5;
const ll inf=1e18;

int n,m,s,t,ss,tt;
vector<pair<int,int>> adj[N];
vector<ll> dist1(N,inf),dist2(N,inf),dist3(N,inf);
ll ans;
ll dp1[N],dp2[N];
bool vis[N];

void dijk(int st,vector<ll> &dist){
    priority_queue<p2,vector<p2>,greater<p2>> pq;
    vector<bool> vis(N);
    dist[st]=0;
    pq.emplace(0,st);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(auto [v,w]:adj[u]){
            if(d+w>=dist[v])continue;
            dist[v]=d+w;
            pq.emplace(d+w,v);
        }
    }
}

void dfs(int u){
    if(vis[u])return;
    vis[u]=true;
    dp1[u]=dist1[u];
    dp2[u]=dist2[u];
    for(auto [v,w]:adj[u]){
        if(dist3[v]+w!=dist3[u])continue;
        dfs(v);
        dp1[u]=min(dp1[u],dp1[v]);
        dp2[u]=min(dp2[u],dp2[v]);
    }
    ans=min(ans,dp1[u]+dist2[u]);
    ans=min(ans,dp2[u]+dist1[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> s >> t >> ss >> tt;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dijk(ss,dist1);
    dijk(tt,dist2);
    dijk(s,dist3);
    ans=dist1[tt];
    dfs(t);
    cout << ans << "\n";
}