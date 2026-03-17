#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

int n,q;
int a[N];
pair<int,int> b[N];
vector<int> adj[N];
int dep[N],par[N],jump[N];

struct Node;
using Ptr = Node*;
struct Node{
    int val;
    Ptr l,r;
    Node():val(0),l(),r(){}
};

Ptr root[N];

void build(int l,int r,Ptr &t){
    t=new Node();
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
}

void update(int l,int r,Ptr &t,Ptr o,int x,int v){
    t=new Node(*o);
    t->val+=v;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t->l,o->l,x,v);
    else update(m+1,r,t->r,o->r,x,v);
}

int query(int l,int r,Ptr tu,Ptr tv,Ptr ta,Ptr tp,int k){
    if(l==r)return l;
    int val=tu->l->val+tv->l->val-ta->l->val-tp->l->val;
    int m=(l+r)/2;
    if(k<=val)return query(l,m,tu->l,tv->l,ta->l,tp->l,k);
    else return query(m+1,r,tu->r,tv->r,ta->r,tp->r,k-val);
}

void dfs(int u,int p){
    dep[u]=dep[p]+1;
    par[u]=p;
    jump[u]=(dep[p]-dep[jump[p]]==dep[jump[p]]-dep[jump[jump[p]]]?jump[jump[p]]:p);
    update(1,n,root[u],root[p],a[u],+1);
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
    }
}

int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    while(dep[u]>dep[v])u=(dep[jump[u]]>=dep[v]?jump[u]:par[u]);
    while(u!=v){
        if(jump[u]!=jump[v])u=jump[u],v=jump[v];
        else u=par[u],v=par[v];
    }
    return u;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        b[i]={a[i],i};
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        a[b[i].second]=i;
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    build(1,n,root[0]);
    dfs(1,0);
    while(q--){
        int u,v,k;
        cin >> u >> v >> k;
        int x=lca(u,v);
        cout << b[query(1,n,root[u],root[v],root[x],root[par[x]],k)].first << "\n";
    }
}