#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;
typedef tuple<ll,ll,ll> t3;

const int N=2e5+5;

int n,m,s,e;
vector<p2> adj[N];
vector<int> pa[N];
ll dp[N];
bool vis[N];
priority_queue<p2,vector<p2>,greater<p2>> pq;
priority_queue<t3,vector<t3>,greater<t3>> pre;

void dfs(int u){
    if(u==0)return;
    dp[u]=0;
    pq.push({0,u});
    for(auto v:pa[u])dfs(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> s >> e;
    for(int i=1;i<=n;i++)dp[i]=1e18;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    pre.push({0,s,0});
    dp[s]=0;
    while(!pre.empty()){
        auto [d,u,p]=pre.top();
        pre.pop();
        if(d==dp[u])pa[u].push_back(p);
        if(vis[u])continue;
        vis[u]=true;
        for(auto [v,w]:adj[u]){
            if(d+w>dp[v])continue;
            dp[v]=d+w;
            pre.push({d+w,v,u});
        }
    }
    dfs(e);
    for(int i=1;i<=n;i++)vis[i]=false;
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(auto [v,w]:adj[u]){
            if(d+w>=dp[v])continue;
            dp[v]=d+w;
            pq.push({d+w,v});
        }
    }
    int q;
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        cout << dp[x] << '\n';
    }
}