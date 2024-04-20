#include"agency.h"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n,m;
int a[N];
vector<pair<int,ll>> adj[N];
int sz[N],pa[N],lv[N],hv[N],hd[N];
ll dp[N],sum[N],dif[N];
int id[N];
vector<pair<ll,int>> vec;

struct PersistSegtree{
    struct node;
    using pnode = node*;
    struct node{
        ll val;
        int freq;
        pnode l,r;
        node():val(0),freq(0),l(nullptr),r(nullptr){}
        node(ll _val,int _freq):val(_val),freq(_freq),l(nullptr),r(nullptr){}
    };
    pnode rt[N];
    void build(int l,int r,pnode &t){
        t=new node();
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
    }
    void build(int t){
        build(1,m,rt[t]);
    }
    void update(int l,int r,pnode &t,pnode k,int x,ll v){
        t=new node(*k);
        t->val+=v;
        t->freq++;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,k->l,x,v);
        else update(m+1,r,t->r,k->r,x,v);
    }
    void update(int t,int k,int x,ll v){
        update(1,m,rt[t],rt[k],x,v);
    }
    ll query(int l,int r,pnode tl,pnode tr,int k){
        if(l==r)return k?tr->val-tl->val:0;
        int m=(l+r)/2;
        ll val=tr->l->val-tl->l->val;
        int freq=tr->l->freq-tl->l->freq;
        if(freq>=k)return query(l,m,tl->l,tr->l,k);
        return query(m+1,r,tl->r,tr->r,k-freq)+val;
    }
    ll query(int l,int r,int k){
        return query(1,m,rt[l],rt[r],k);
    }
}pst;

void dfs(int u,int p=0){
    sz[u]=1;
    for(auto [v,w]:adj[u])if(v!=p){
        dp[v]=dp[u]+w;
        pa[v]=u;
        lv[v]=lv[u]+1;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u,int p=0){
    if(!hd[u])hd[u]=u;
    if(hv[u])hd[hv[u]]=hd[u],hld(hv[u],u);
    for(auto [v,w]:adj[u])if(v!=p&&v!=hv[u])hld(v,u);
}

int lca(int u,int v){
    while(hd[u]!=hd[v]){
        if(lv[hd[u]]<lv[hd[v]])swap(u,v);
        u=pa[hd[u]];
    }
    return lv[u]<lv[v]?u:v;
}

ll dist(int u,int v){
    return dp[u]+dp[v]-2*dp[lca(u,v)];
}

void init(int _n,vector<int> _a,vector<vector<int>> _rd){
    n=_n,m=_a.size();
    for(int i=1;i<=m;i++)a[i]=_a[i-1]+1;
    for(int i=0;i<n-1;i++){
        int u=_rd[i][0]+1,v=_rd[i][1]+1,w=_rd[i][2];
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    int s=_rd[n-1][0]+1,t=_rd[n-1][1]+1,c=_rd[n-1][2];
    dfs(1);
    hld(1);
    for(int i=2;i<=m;i++){
        int u=a[i-1],v=a[i];
        ll d=dist(a[i-1],a[i]);
        dif[i]=c+min(dist(u,s)+dist(t,v),dist(u,t)+dist(s,v))-d;
        sum[i]=sum[i-1]+d;
        vec.emplace_back(dif[i],i);
    }
    sort(vec.begin(),vec.end());
    for(int i=0;i<m-1;i++)id[vec[i].second]=i+1;
    pst.build(1);
    for(int i=2;i<=m;i++)pst.update(i,i-1,id[i],dif[i]);
}

ll min_distance(int l,int r,int x){
    l++,r++;
    return sum[r]-sum[l]+pst.query(l,r,x);
}