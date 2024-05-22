#include<bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N=1e5+5;

int n,q;
vector<int> adj[N];
int a[N];
int l[N],r[N];
int sz[N],lv[N],hv[N],hd[N],pa[N];
ull hsh[N];

struct Node;
using Ptr = Node*;
struct Node{
    ull val;
    Ptr l,r;
    Node():val(0),l(nullptr),r(nullptr){}
};

Ptr rt[N];

void build(int l,int r,Ptr &t){
    t=new Node();
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
}

void update(int l,int r,Ptr &t,Ptr p,int x,ull v){
    t=new Node(*p);
    t->val+=v;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t->l,p->l,x,v);
    else update(m+1,r,t->r,p->r,x,v);
}

int query(int l,int r,Ptr u1,Ptr v1,Ptr l1,Ptr p1,Ptr u2,Ptr v2,Ptr l2,Ptr p2,int x){
    ull val1=u1->val+v1->val-l1->val-p1->val;
    ull val2=u2->val+v2->val-l2->val-p2->val;
    if(r<x||val1==val2)return -1;
    if(l==r)return l;
    int m=(l+r)/2;
    int res=query(l,m,u1->l,v1->l,l1->l,p1->l,u2->l,v2->l,l2->l,p2->l,x);
    if(res!=-1)return res;
    return query(m+1,r,u1->r,v1->r,l1->r,p1->r,u2->r,v2->r,l2->r,p2->r,x);
}

void dfs(int u,int p=0){
    sz[u]=1;
    pa[u]=p;
    lv[u]=lv[p]+1;
    update(1,N,rt[u],rt[p],a[u],hsh[a[u]]);
    for(auto v:adj[u])if(v!=p){
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u,int p=0){
    if(!hd[u])hd[u]=u;
    if(hv[u])hd[hv[u]]=hd[u],hld(hv[u],u);
    for(auto v:adj[u])if(v!=p&&v!=hv[u])hld(v,u);
}

int lca(int u,int v){
    while(hd[u]!=hd[v]){
        if(lv[hd[u]]<lv[hd[v]])swap(u,v);
        u=pa[hd[u]];
    }
    return lv[u]<lv[v]?u:v;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<N;i++)hsh[i]=rng();
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    build(1,N,rt[0]);
    dfs(1);
    hld(1);
    cin >> q;
    while(q--){
        int u1,v1,u2,v2,k;
        cin >> u1 >> v1 >> u2 >> v2 >> k;
        int l1=lca(u1,v1),l2=lca(u2,v2);
        int p=0;
        vector<int> ans;
        while(k--){
            p=query(1,N,rt[u1],rt[v1],rt[l1],rt[pa[l1]],rt[u2],rt[v2],rt[l2],rt[pa[l2]],p+1);
            if(p==-1)break;
            ans.emplace_back(p);
        }
        cout << ans.size();
        for(auto x:ans)cout << " " << x;
        cout << "\n";
    }
}