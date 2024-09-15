#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int LG=17;

int n,q;
int a[N];
pair<int,int> b[N];
vector<int> adj[N];
int par[LG][N],dep[N];

struct PersistentSegmentTree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        int val;
        Ptr l,r;
        Node(int _val):val(_val),l(nullptr),r(nullptr){}
    };
    Ptr root[N];
    void build(int l,int r,Ptr &t){
        t=new Node(0);
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
    }
    void build(int cur){
        build(1,n,root[cur]);
    }
    void update(int l,int r,Ptr &t,Ptr o,int x,int v){
        t=new Node(*o);
        if(l==r){
            t->val++;
            return;
        }
        int m=(l+r)/2;
        if(x<=m){
            update(l,m,t->l,o->l,x,v);
        }else{
            update(m+1,r,t->r,o->r,x,v);
        }
        t->val=t->l->val+t->r->val;
    }
    void update(int cur,int pre,int x,int v){
        update(1,n,root[cur],root[pre],x,v);
    }
    int bsearch(int l,int r,Ptr tu,Ptr tv,Ptr tlca,Ptr tpar,int k){
        if(l==r)return l;
        int m=(l+r)/2;
        int cnt=tu->l->val+tv->l->val-tlca->l->val-tpar->l->val;
        if(cnt>=k){
            return bsearch(l,m,tu->l,tv->l,tlca->l,tpar->l,k);
        }else{
            return bsearch(m+1,r,tu->r,tv->r,tlca->r,tpar->r,k-cnt);
        }
    }
    int bsearch(int u,int v,int lca,int par,int k){
        return bsearch(1,n,root[u],root[v],root[lca],root[par],k);
    }
}pst;

void dfs(int u,int p){
    dep[u]=dep[p]+1;
    par[0][u]=p;
    for(int i=1;i<LG;i++){
        par[i][u]=par[i-1][par[i-1][u]];
    }
    pst.update(u,p,a[u],+1);
    for(auto v:adj[u]){
        if(v!=p){
            dfs(v,u);
        }
    }
}

int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    for(int i=LG-1;i>=0;i--){
        int x=par[i][u];
        if(dep[x]>=dep[v]){
            u=x;
        }
    }
    assert(dep[u]==dep[v]);
    if(u==v){
        return u;
    }
    for(int i=LG-1;i>=0;i--){
        int x=par[i][u];
        int y=par[i][v];
        if(x!=y){
            u=x;
            v=y;
        }
    }
    assert(u!=v);
    assert(par[0][u]==par[0][v]);
    return par[0][u];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        b[i]={a[i],i};
    }
    for(int i=1;i<=n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        a[b[i].second]=i;
    }
    pst.build(0);
    dfs(1,0);
    while(q--){
        int u,v,k;
        cin >> u >> v >> k;
        int x=lca(u,v);
        cout << b[pst.bsearch(u,v,x,par[0][x],k)].first << "\n";
    }
}