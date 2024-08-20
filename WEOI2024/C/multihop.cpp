#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;

int n,c;
vector<int> adj[N];
int sz[N],hv[N],hd[N],disc[N],p[N],lv[N],pos[N];
int timer;
ll a[N],b[N];

struct Node{
    ll aa,ab,ba,bb;
    Node(){}
    Node(int i){
        aa=a[i];
        ab=b[i]+c;
        ba=c;
        bb=c;
    }
    friend Node operator+(Node l,Node r){
        Node res;
        res.aa=min(l.aa+r.aa,l.ab+r.ba);
        res.ab=min(l.aa+r.ab,l.ab+r.bb);
        res.ba=min(l.ba+r.aa,l.bb+r.ba);
        res.bb=min(l.ba+r.ab,l.bb+r.bb);
        return res;
    }
};

struct SegTree1{
    Node t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Node(pos[l]));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    Node query(int l,int r,int i,int x,int y){
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        if(y<=m)return query(l,m,i*2,x,y);
        if(m+1<=x)return query(m+1,r,i*2+1,x,y);
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    Node query(int x,int y){
        return query(1,n,1,x,y);
    }
}segdown;

struct SegTree2{
    Node t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Node(pos[l]));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2+1]+t[i*2];
    }
    void build(){
        build(1,n,1);
    }
    Node query(int l,int r,int i,int x,int y){
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        if(y<=m)return query(l,m,i*2,x,y);
        if(m+1<=x)return query(m+1,r,i*2+1,x,y);
        return query(m+1,r,i*2+1,x,y)+query(l,m,i*2,x,y);
    }
    Node query(int x,int y){
        return query(1,n,1,x,y);
    }
}segup;

void dfs(int u){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p[u]){
        p[v]=u;
        lv[v]=lv[u]+1;
        dfs(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u){
    disc[u]=++timer;
    pos[timer]=u;
    if(!hd[u])hd[u]=u;
    if(hv[u])hd[hv[u]]=hd[u],hld(hv[u]);
    for(auto v:adj[u])if(v!=p[u]&&v!=hv[u])hld(v);
}

int lca(int u,int v){
    while(hd[u]!=hd[v]){
        if(hd[lv[hd[u]]<lv[hd[v]]])swap(u,v);
        u=p[hd[u]];
    }
    return lv[u]<lv[v]?u:v;
}

vector<Node> ascend(int u,int v){
    vector<Node> res;
    if(u==v)return res;
    while(hd[u]!=hd[v]){
        res.emplace_back(segup.query(disc[hd[u]],disc[u]));
        u=p[hd[u]];
    }
    if(u!=v)res.emplace_back(segup.query(disc[v]+1,disc[u]));
    return res;
}

vector<Node> decend(int u,int v){
    vector<Node> res;
    if(u==v)return res;
    u=p[u];
    while(hd[u]!=hd[v]){
        res.emplace_back(segdown.query(disc[hd[u]],disc[u]));
        u=p[hd[u]];
    }
    res.emplace_back(segdown.query(disc[v],disc[u]));
    reverse(res.begin(),res.end());
    return res;
}

void init(int _n,int _c,vector<int> _a,vector<int> _b,vector<int> _u,vector<int> _v){
    n=_n,c=_c;
    for(int i=1;i<=n;i++){
        b[i]=_b[i-1];
        a[i]=min((ll)_a[i-1],b[i]+c);
    }
    for(int i=0;i<n-1;i++){
        int u=_u[i]+1,v=_v[i]+1;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    hld(1);
    segup.build();
    segdown.build();
}

ll query(int u,int v){
    u++,v++;
    if(u==v)return 0LL;
    int anc=lca(u,v);
    auto as=ascend(u,anc),ds=decend(v,anc);
    if(as.empty()){
        Node res=ds[0];
        for(int i=1;i<ds.size();i++)res=res+ds[i];
        return res.aa;
    }else{
        Node res=as[0];
        for(int i=1;i<as.size();i++)res=res+as[i];
        for(auto x:ds)res=res+x;
        return res.aa;
    }
    return -1LL;
}
