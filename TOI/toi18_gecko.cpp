#include<bits/stdc++.h>

using namespace std;

using P = pair<int,int>;

const int N=2e4+5;

int n,m,k,p;
int g[N];
vector<P> adj[N];
priority_queue<P,vector<P>,greater<P>> pq;
int dp[N],par[N];
bool mark[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k >> p;
    for(int i=0;i<k;i++){
        cin >> g[i];
    }
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<int> 
    for(int i=0;i<n;i++)dp[i]=2e9;
    pq.emplace(dp[p]=0,p);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dp[u])continue;
        for(auto [v,w]:adj[u]){
            if(d+w<dp[v]){
                pq.emplace(dp[v]=d+w,v);
                par[v]=u;
            }
        }
    }
    mark[p]=true;
    for(int i=0;i<k;i++){
        int u=g[i];
        cout << dp[u] << " \n"[i==k-1];
        while(!mark[u]){
            mark[u]=true;
            u=par[u];
        }
    }
    cout << ans.size() << "\n";
    reverse(ans.begin(),ans.end());
    for(auto [u,v]:ans){
        cout << u << " " << v << "\n";
    }
}