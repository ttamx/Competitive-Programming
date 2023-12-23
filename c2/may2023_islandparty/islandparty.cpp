#include <bits/stdc++.h>
#include "islandparty.h"

using namespace std;

typedef long long ll;
typedef pair<int,ll> p2;

const int N=1e5+5;
const int K=20;

int n;
ll a[N];
vector<int> adj[N];
int sz[N],cp[N],lv[N];
ll dist[N][K];
bool used[N];
vector<p2> dp[N],dp2[N];

int getsz(int u,int p=-1){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=getsz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=-1){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt/2)return centroid(v,cnt,u);
    return u;
}

void dfs(int u,vector<p2> &vec,ll d,int l,int p=-1){
    d^=a[u];
    dist[u][l]=d;
    vec.emplace_back(u,d);
    for(auto v:adj[u])if(v!=p&&!used[v])dfs(v,vec,d,l,u);
}

void decom(int u,int p=-1){
    cp[u]=p;
    used[u]=true;
    dp[u].emplace_back(u,a[u]);
    dist[u][lv[u]]=a[u];
    for(auto v:adj[u])if(!used[v]){
        int c=centroid(v,getsz(v));
        dfs(v,dp2[c],a[u],lv[u]);
        sort(dp2[c].begin(),dp2[c].end());
        for(auto x:dp2[c])dp[u].emplace_back(x);
        for(int i=1;i<dp2[c].size();i++)dp2[c][i].second^=dp2[c][i-1].second;
        lv[c]=lv[u]+1;
        decom(c,u);
    }
    sort(dp[u].begin(),dp[u].end());
    for(int i=1;i<dp[u].size();i++)dp[u][i].second^=dp[u][i-1].second;
}

p2 query(vector<p2> &vec,int l,int r){
    p2 res(0,0);
    auto it=lower_bound(vec.begin(),vec.end(),p2(l,0));
    if(it!=vec.begin()){
        res.first^=int(--it-vec.begin()+1)&1;
        res.second^=it->second;
    }
    it=lower_bound(vec.begin(),vec.end(),p2(r+1,0));
    if(it!=vec.begin()){
        res.first^=int(--it-vec.begin()+1)&1;
        res.second^=it->second;
    }
    return res;
}

void init(int N, int T, vector<long long> A, vector<int> U, vector<int> V) {
    n=N;
    for(int i=0;i<n;i++)a[i]=A[i];
    for(int i=0;i<n-1;i++){
        int u=U[i],v=V[i];
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    decom(centroid(0,getsz(0)));
}

long long find_drunkenness(int L, int R, int X) {
    ll ans=0;
    for(int u=X,p=-1;u!=-1;p=u,u=cp[u]){
        auto [s1,v1]=query(dp[u],L,R);
        ans^=v1;
        bool ok=s1;
        if(p!=-1){
            auto [s2,v2]=query(dp2[p],L,R);
            ans^=v2;
            ok^=s2;
        }
        if(ok)ans^=dist[X][lv[u]]^a[u];
    }
    return ans;
}