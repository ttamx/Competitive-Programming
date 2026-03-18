#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;
const int K=1<<20;

int n,q;
int a[N];
vector<int> adj[N];
int par[N],sz[N],hv[N],disc[N],hd[N];
int timer=0;
int ans[N];
priority_queue<pair<int,int>> pq;

struct Segtree{
    int t[K],lz[K];
    void apply(int i,int v){
        t[i]+=v;
        lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        push(i);
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

void dfs(int u){
    sz[u]=1;
    for(auto v:adj[u]){
        dfs(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u){
    if(!hd[u])hd[u]=u;
    disc[u]=++timer;
    if(hv[u])hd[hv[u]]=hd[u],hld(hv[u]);
    for(auto v:adj[u])if(v!=hv[u])hld(v);
}

int query(int u){
    int res=seg.query(disc[u]+sz[u],n);
    int last=disc[u]-1;
    while(u){
        if(disc[u]<last)res=max(res,seg.query(disc[u]+1,last));
        last=disc[hd[u]]-1;
        u=par[hd[u]];
    }
    if(last>0)res=max(res,seg.query(1,last));
    return res;
}

void update(int u){
    while(u){
        seg.update(disc[hd[u]],disc[u],+1);
        u=par[hd[u]];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=2;i<=n;i++){
        cin >> par[i];
        adj[par[i]].emplace_back(i);
    }
    for(int i=1;i<=n;i++)cin >> a[i];
    dfs(1);
    hld(1);
    pq.emplace(a[1],1);
    for(int i=0;i<n;i++){
        int u=pq.top().second;
        pq.pop();
        for(auto v:adj[u])pq.emplace(a[v],v);
        ans[u]=i-query(u);
        update(u);
    }
    for(int i=1;i<=q;i++){
        int x;
        cin >> x;
        cout << ans[x] << " \n"[i==q];
    }
}