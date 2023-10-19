#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<ll,ll,ll> t3;

const int N=100005;
const int M=250005;
const ll inf=1e18;

int n,m,k;
int c[M];
vector<t3> adj[N];
set<t3> pq;
map<int,int> mp[N];
vector<ll> dp[N];
vector<int> col[N];
vector<bool> vis[N];

long long plan(int N, int M, int K, vector<int> A, vector<int> B, vector<int> L, vector<int> C, vector<int> T) {
    n=N,m=M,k=K;
    for(int i=0;i<k;i++)c[i]=T[i];
    for(int i=0;i<m;i++){
        int u=A[i],v=B[i],w=L[i],t=C[i];
        adj[u].emplace_back(v,w,t);
        adj[v].emplace_back(u,w,t);
        mp[u][t],mp[v][t];
    }
    for(int i=0;i<n;i++){
        for(auto &[x,y]:mp[i]){
            y=dp[i].size();
            dp[i].emplace_back(inf);
            col[i].emplace_back(x);
            vis[i].emplace_back(false);
        }
    }
    for(int i=0;i<n;i++){
        for(auto &[v,w,t]:adj[i]){
            t=mp[v][t];
        }
    }
    dp[0].emplace_back(0);
    col[0].emplace_back(-1);
    vis[0].emplace_back(false);
    pq.emplace(0,0,dp[0].size()-1);
    while(!pq.empty()){
        auto [d,u,s]=*pq.begin();
        pq.erase(pq.begin());
        if(vis[u][s])continue;
        vis[u][s]=true;
        s=col[u][s];
        for(auto [v,w,t]:adj[u]){
            int ct=col[v][t];
            ll val=d+w+(ct==s?0:c[ct]);
            if(dp[v][t]>val){
                if(dp[v][t]<inf)pq.erase({dp[v][t],v,t});
                dp[v][t]=val;
                pq.emplace(val,v,t);
            }
        }
    }
    ll ans=inf;
    for(auto x:dp[n-1])ans=min(ans,x);
    return ans;
}