#include <bits/stdc++.h>
#include "war.h"

using namespace std;

using ll = long long;

const int N=2e5+5;
const int LG=18;
const ll INF=1e11;
const ll INF2=1e12;

int n;
ll a[N],val[N];
vector<int> adj[N];
int sz[N],par[N],lv[N];
bool used[N];
int tin[N][LG],tout[N][LG],l[N],r[N];
int timer;
bool t[N];

struct SegTree{
    int n;
    vector<ll> t,lz;
    SegTree(){}
    void init(int _n){
        n=_n;
        t.assign(4*n,0LL);
        lz.assign(4*n,0LL);
        build();
    }
    void apply(int i,ll v){
        t[i]+=v;
        lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=val[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,ll v){
        update(1,n,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return INF2;
        if(x<=l&&r<=y)return t[i];
        push(i);
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg[N];

void dfs(int u,int l,ll d=0,int p=-1){
    if(u>=n)d+=a[u];
    tin[u][l]=++timer;
    val[timer]=u<n?INF+d:INF2;
    for(auto v:adj[u])if(v!=p&&!used[v])dfs(v,l,d,u);
    tout[u][l]=timer;
}

int getsz(int u,int p=-1){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=getsz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=-1){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt/2)return centroid(v,cnt,u);
    return u;
}

int decom(int u,int dep=0){
    u=centroid(u,getsz(u));
    used[u]=true;
    lv[u]=dep;
    timer=0;
    dfs(u,lv[u]);
    seg[u].init(timer);
    for(auto v:adj[u])if(!used[v]){
        int c=decom(v,dep+1);
        par[c]=u;
        l[c]=tin[v][dep];
        r[c]=tin[v][dep];
    }
    return u;
}

void init(int _n,vector<int> A,vector<int> B,vector<int> W){
    n=_n;
    for(int i=0;i<n;i++)a[i]=INF;
    for(int i=0;i<n-1;i++){
        int u=A[i],v=B[i];
        adj[u].emplace_back(n+i);
        adj[v].emplace_back(n+i);
        adj[n+i].emplace_back(u);
        adj[n+i].emplace_back(v);
        a[n+i]=W[i];
    }
    par[decom(0)]=-1;
}

void toggle_hospital(int x){
    t[x]^=true;
    ll val=t[x]?-INF:INF;
    for(int u=x;u!=-1;u=par[u])seg[u].update(tin[x][lv[u]],tin[x][lv[u]],val);
}

void toggle_road(int x){
    x+=n;
    t[x]^=true;
    ll val=t[x]?INF:-INF;
    a[x]+=val;
    for(int u=x;u!=-1;u=par[u])seg[u].update(tin[x][lv[u]],tout[x][lv[u]],val);
}

ll nearest_hospital(int x){
    if(t[x])return 0LL;
    ll res=min(INF,seg[x].t[1]);
    for(int u=par[x],ch=x;u!=-1;ch=u,u=par[u]){
        ll du=seg[u].query(tin[x][lv[u]],tin[x][lv[u]])-INF;
        ll dv=min(seg[u].query(1,l[ch]-1),seg[u].query(r[ch]+1,seg[u].n));
        ll d=du+dv;
        if(u>=n)d-=a[u];
        res=min(res,d);
    }
    return res<INF?res:-1LL;
}