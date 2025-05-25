#include<bits/stdc++.h>

using namespace std;

const int N=100005;
const int K=1<<18;
const int LG=17;
const int INF=INT_MAX/2;

int n,q;
int par[LG][N],disc[N],id[N],dep[N];
vector<int> adj[N];
int timer;

void dfs(int u){
    disc[u]=++timer;
    id[timer]=u;
    for(auto v:adj[u]){
        dep[v]=dep[u]+1;
        dfs(v);
    }
}

int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    for(int i=LG-1;i>=0;i--)if(dep[par[i][u]]>=dep[v])u=par[i][u];
    if(u==v)return u;
    for(int i=LG-1;i>=0;i--)if(par[i][u]!=par[i][v])u=par[i][u],v=par[i][v];
    return par[0][u];
}

struct Info{
    int mn,mx,mn2,mx2;
    friend Info operator+(const Info &l,const Info &r){
        Info res;
        if(l.mn<r.mn)res.mn=l.mn,res.mn2=min(l.mn2,r.mn);
        else res.mn=r.mn,res.mn2=min(l.mn,r.mn2);
        if(l.mx>r.mx)res.mx=l.mx,res.mx2=max(l.mx2,r.mx);
        else res.mx=r.mx,res.mx2=max(l.mx,r.mx2);
        return res;
    }
};

struct Segtree{
    Info t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Info{disc[l],disc[l],INF,-INF});
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){build(1,n,1);}
    Info query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Info{INF,-INF,INF,-INF};
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    Info query(int x,int y){return query(1,n,1,x,y);}
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=2;i<=n;i++){
        cin >> par[0][i];
        adj[par[0][i]].emplace_back(i);
    }
    dfs(1);
    seg.build();
    par[0][1]=1;
    for(int i=1;i<LG;i++)for(int u=1;u<=n;u++)par[i][u]=par[i-1][par[i-1][u]];
    while(q--){
        int l,r;
        cin >> l >> r;
        auto res=seg.query(l,r);
        pair<int,int> ans(-1,-1);
        ans=max(ans,{dep[lca(id[res.mn],id[res.mx2])],id[res.mx]});
        ans=max(ans,{dep[lca(id[res.mn2],id[res.mx])],id[res.mn]});
        cout << ans.second << " " << ans.first << "\n";
    }
}