#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e4+5;
const int K=1<<17;

int n,m,k;
int pos[N];
bool vis[N];
ll a[N],qs[N],dp[N],mn[N];
vector<pair<int,ll>> adj[N];
vector<ll> in;

struct segtree{
    ll s[K];
    void build(int l,int r,int i){
        s[i]=1e18;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void update(int l,int r,int i,int x,ll v){
        if(r<x||x<l)return;
        if(l==r)return void(s[i]=min(s[i],v));
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        s[i]=min(s[i*2],s[i*2+1]);
    }
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 1e18;
        if(x<=l&&r<=y)return s[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}seg[2];

long long minimum_energy(int N, int M, int K,vector<int> A,vector<int> L,vector<int> R,vector<int> C){
    n=N,m=M,k=K;
    for(int i=1;i<=n;i++){
        a[i]=A[i-1];
        qs[i]=qs[i-1]+a[i];
        dp[i]=1e18;
        adj[i].push_back({i-1,a[i]});
        adj[i-1].push_back({i,a[i]});
        in.push_back(a[i]);
    }
    sort(in.begin(),in.end());
    in.erase(unique(in.begin(),in.end()),in.end());
    for(int i=1;i<=n;i++)pos[i]=lower_bound(in.begin(),in.end(),a[i])-in.begin()+1;
    int sz=in.size();
    for(int i=0;i<m;i++){
        adj[L[i]].push_back({R[i]+1,C[i]});
        adj[R[i]+1].push_back({L[i],C[i]});
    }
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    auto dijk=[&](){
        for(int i=0;i<=n;i++)vis[i]=false;
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(vis[u])continue;
            vis[u]=true;
            for(auto [v,w]:adj[u]){
                if(d+w<dp[v]){
                    dp[v]=d+w;
                    pq.push({d+w,v});
                }
            }
        }
    };
    pq.push({0,0});
    dijk();
    for(int l=1;l<=k;l++){
        seg[0].build(1,n,1);
        seg[1].build(1,n,1);
        for(int i=n;i>=0;i--){
            ll q1=1e18,q2=1e18;
            q1=seg[0].query(1,sz,1,1,pos[i+1])+a[i+1]*a[i+1];
            q2=seg[1].query(1,sz,1,pos[i+1],n)-a[i+1]*a[i+1];
            seg[0].update(1,sz,1,pos[i],dp[i]-a[i]*a[i]);
            seg[1].update(1,sz,1,pos[i],dp[i]+a[i]*a[i]);
            mn[i]=min(q1,q2);
        }
        seg[0].build(1,n,1);
        seg[1].build(1,n,1);
        for(int i=0;i<=n;i++){
            ll q1=1e18,q2=1e18;
            q1=seg[0].query(1,sz,1,1,pos[i])+a[i]*a[i];
            q2=seg[1].query(1,sz,1,pos[i],n)-a[i]*a[i];
            seg[0].update(1,sz,1,pos[i+1],dp[i]-a[i+1]*a[i+1]);
            seg[1].update(1,sz,1,pos[i+1],dp[i]+a[i+1]*a[i+1]);
            mn[i]=min({mn[i],q1,q2});
        }
        for(int i=1;i<=n;i++){
            if(mn[i]<dp[i]){
                dp[i]=mn[i];
                pq.push({dp[i],i});
            }
        }
        dijk();
    }
    return dp[n];
}
