#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

typedef long long ll;

int n,m,q;
int c[N];
int sz[N],heavy[N],chain[N],head[N],pos[N],chainid,posid;
int lv[N],pa[N][20];
vector<int> adj[N];

struct segtree{
    ll t[K],lz[K];
    void build(int l,int r,int i){
        t[i]=0;
        lz[i]=-1;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(1,n,1);
    }
    void pushlz(int l,int r,int i){
        if(lz[i]==-1)return;
        t[i]=(r-l+1)*lz[i];
        if(l<r){
            lz[i*2]=lz[i];
            lz[i*2+1]=lz[i];
        }
        lz[i]=-1;
    }
    void update(int l,int r,int i,int x,int y,ll v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y){
            lz[i]=v;
            pushlz(l,r,i);
            return;
        }
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,ll v){
        update(1,n,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

void dfs(int u,int p){
    sz[u]=1;
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[heavy[u]])heavy[u]=v;
    }
}

void hld(int u,int p){
    pos[u]=++posid;
    chain[u]=chainid;
    if(heavy[u])hld(heavy[u],u);
    for(auto v:adj[u]){
        if(v==p||v==heavy[u])continue;
        head[++chainid]=v;
        hld(v,u);
    }
}

void updateup(int st,int ed,ll val){
    while(chain[st]!=chain[ed]){
        seg.update(pos[head[chain[st]]],pos[st],val);
        st=pa[head[chain[st]]][0];
    }
    seg.update(pos[ed]+1,pos[st],val);
}

ll queryup(int st,int ed){
    ll res=0;
    while(chain[st]!=chain[ed]){
        res+=seg.query(pos[head[chain[st]]],pos[st]);
        st=pa[head[chain[st]]][0];
    }
    res+=seg.query(pos[ed]+1,pos[st]);
    return res;
}

int lca(int a,int b){
    if(lv[a]<lv[b])swap(a,b);
    for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
    if(a==b)return a;
    for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
    return pa[a][0];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,0);
    head[++chainid]=1;
    hld(1,0);
    for(int i=1;i<=m;i++)cin >> c[i];
    seg.build();
    while(q--){
        seg.update(1,n,0);
        int l,r;
        cin >> l >> r;
        int res=0;
        int rt=c[l];
        for(int i=l+1;i<=r;i++){
            int u=c[i];
            int v=c[i-1];
            int LCA=lca(u,v);
            updateup(u,LCA,1);
            updateup(v,LCA,1);
        }
        cout << seg.query(1,n)+1 << '\n';
    }
}