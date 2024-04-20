#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

int n,q,root;
int sz[N],hv[N],dir[N],tin[N],tout[N],pos[N];
int timer=0;
ll ans[N];
vector<int> adj[N];
vector<pair<int,ll>> qr[N];
vector<tuple<int,int,ll>> qr2[N];

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

struct node;
using pnode = node*;
struct node{
    int val;
    pnode l,r;
    node(int _val):val(_val),l(nullptr),r(nullptr){}
};
pnode rt[N];

void build(int l,int r,pnode &t){
    t=new node(0);
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
}

void build(pnode &t){
    build(1,n,t);
}

void update(int l,int r,pnode &t,pnode k,int x,int v){
    if(x<l||r<x)return;
    t=new node(*k);
    t->val+=v;
    if(l==r)return;
    int m=(l+r)/2;
    update(l,m,t->l,k->l,x,v);
    update(m+1,r,t->r,k->r,x,v);
}

void update(pnode &t,pnode k,int x,int v){
    update(1,n,t,k,x,v);
}

int query(int l,int r,pnode t1,pnode t2,int k){
    if(l==r)return l;
    int m=(l+r)/2;
    int val=t1->l->val-t2->l->val;
    if(val>=k)return query(l,m,t1->l,t2->l,k);
    return query(m+1,r,t1->r,t2->r,k-val);
}

int query(pnode t1,pnode t2,int k){
    return query(1,n,t1,t2,k);
}

void predfs(int u,int p=0){
    tin[u]=++timer;
    pos[timer]=u;
    sz[u]=1;
    for(auto v:adj[u])if(v!=p){
        predfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
    tout[u]=timer;
}

void dfs(int u,int p=0){
    f.update(u,sz[u]);
    for(auto [i,val]:qr[u]){
        int l=1,r=n;
        while(l<r){
            int m=(l+r)/2;
            if(f.query(m)>=val)r=m;
            else l=m+1;
        }
        ans[i]+=1LL*(l-1)*n;
        qr2[l].emplace_back(i,dir[l],val-f.query(l-1));
    }
    for(auto v:adj[u])if(v!=p){
        f.update(u,-sz[v]);
        dir[u]=v;
        dfs(v,u);
        f.update(u,sz[v]);
    }
    f.update(u,-sz[u]);
}

void dfs2(int u,int p=0){
    for(auto v:adj[u])if(v!=p)dfs2(v,u);
    update(rt[u],rt[hv[u]],u,1);
    for(auto v:adj[u])if(v!=p&&v!=hv[u]){
        for(int t=tin[v];t<=tout[v];t++)update(rt[u],rt[u],pos[t],1);
    }
    for(auto [i,v,val]:qr2[u])ans[i]+=query(rt[u],rt[v],val)-1;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        if(x==0){
            root=i;
            continue;
        }
        adj[i].emplace_back(x);
        adj[x].emplace_back(i);
    }
    for(int i=1;i<=q;i++){
        ll x;
        cin >> x;
        int u=(x-1)/n+1;
        ans[i]=1LL*(u-1)*n*n;
        qr[u].emplace_back(i,x-1LL*(u-1)*n);
    }
    predfs(root);
    dfs(root);
    build(rt[0]);
    dfs2(root);
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}