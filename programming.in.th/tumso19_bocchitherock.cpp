#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n,m,k;
ll dp[N];
bool vis[N];
vector<pair<int,ll>> adj[N];
priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n;i++)dp[i]=1e18;
    for(int i=0;i<m;i++){
        int u,v;
        ll w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    cin >> k;
    for(int i=0;i<k;i++){
        int x;
        ll c;
        cin >> x >> c;
        if(c<dp[x]){
            dp[x]=c;
            pq.emplace(c,x); 
        }
    }
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        if(u==0)break;
        for(auto [v,w]:adj[u]){
            if(d+w<dp[v]){
                dp[v]=d+w;
                pq.emplace(d+w,v);
            }
        }
    }
    cout << dp[0] << '\n';
}