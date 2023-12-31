#include "factories.h"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

int n;
vector<vector<pair<int,int>>> adj;
vector<int> sz,lv,pa;
vector<bool> used;
vector<vector<ll>> dist;
vector<ll> dp;

int dfssz(int u,int p=-1){
    sz[u]=1;
    for(auto [v,w]:adj[u])if(v!=p&&!used[v])sz[u]+=dfssz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=-1){
    for(auto [v,w]:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt/2)return centroid(v,cnt,u);
    return u;
}

void filldist(int u,int l,ll d,int p=-1){
    dist[l][u]=d;
    for(auto [v,w]:adj[u])if(v!=p&&!used[v])filldist(v,l,d+w,u);
}

void decom(int u,int p=-1,int l=0){
    u=centroid(u,dfssz(u));
    pa[u]=p;
    lv[u]=l;
    used[u]=true;
    if(l==dist.size())dist.emplace_back(vector<ll>(n));
    for(auto [v,w]:adj[u])if(!used[v])filldist(v,l,w);
    for(auto [v,w]:adj[u])if(!used[v])decom(v,u,l+1);
}

void update(int st){
    for(int u=st;u!=-1;u=pa[u])dp[u]=min(dp[u],dist[lv[u]][st]);
}

ll query(int st){
    ll res=INF;
    for(int u=st;u!=-1;u=pa[u])res=min(res,dist[lv[u]][st]+dp[u]);
    return res;
}

void clear(int st){
    for(int u=st;u!=-1;u=pa[u])dp[u]=INF;
}

void Init(int N, int A[], int B[], int D[]){
    n=N;
    adj.assign(n,{});
    sz=lv=pa=vector<int>(n);
    used.assign(n,0);
    dp.assign(n,INF);
    for(int i=0;i<n-1;i++){
        int u=A[i],v=B[i],w=D[i];
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    decom(1);
}

ll Query(int S, int X[], int T, int Y[]) {
    ll ans=INF;
    for(int i=0;i<S;i++)update(X[i]);
    for(int i=0;i<T;i++)ans=min(ans,query(Y[i]));
    for(int i=0;i<S;i++)clear(X[i]);
    return ans;
}