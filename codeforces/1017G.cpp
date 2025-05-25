#include<bits/stdc++.h>

using namespace std;

const int N=100005;
const int K=1<<18;

int n,q;
int par[N],sz[N],hv[N],head[N],disc[N];
vector<int> adj[N];
int timer;

struct Info{
    int ans,sum;
    Info():ans(-1),sum(0){}
    Info(int _ans,int _sum):ans(_ans),sum(_sum){}
    friend Info operator+(const Info &l,const Info &r){return Info(max(l.ans+r.sum,r.ans),l.sum+r.sum);}
};

struct Segtree{
    Info t[K];
    bool lz[K];
    void apply(int l,int r,int i,bool v){if(v)t[i]={-1,-(r-l+1)},lz[i]=true;}
    void push(int l,int m,int r,int i){apply(l,m,i*2,lz[i]),apply(m+1,r,i*2+1,lz[i]);lz[i]=false;}
    void pull(int i){t[i]=t[i*2]+t[i*2+1];}
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Info(-1,-1));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        pull(i);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i].ans=t[i].sum=t[i].sum+v);
        int m=(l+r)/2;
        push(l,m,r,i);
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        pull(i);
    }
    void clear(int l,int r,int i,int x,int y){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,i,true);
        int m=(l+r)/2;
        push(l,m,r,i);
        clear(l,m,i*2,x,y);
        clear(m+1,r,i*2+1,x,y);
        pull(i);
    }
    Info query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Info(-1,0);
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        push(l,m,r,i);
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    void build(){build(1,n,1);}
    void update(int x,int v){update(1,n,1,x,v);}
    void clear(int x,int y){clear(1,n,1,x,y);}
    Info query(int x,int y){return query(1,n,1,x,y);}
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
    disc[u]=++timer;
    if(!head[u])head[u]=u;
    if(hv[u])head[hv[u]]=head[u],hld(hv[u]);
    for(auto v:adj[u])if(v!=hv[u])hld(v);
}

Info query(int u){
    Info res(-1,0);
    for(;u;u=par[head[u]])res=seg.query(disc[head[u]],disc[u])+res;
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=2;i<=n;i++){
        cin >> par[i];
        adj[par[i]].emplace_back(i);
    }
    dfs(1);
    hld(1);
    seg.build();
    while(q--){
        int t,u;
        cin >> t >> u;
        if(t==1)seg.update(disc[u],+1);
        else if(t==2){
            seg.clear(disc[u],disc[u]+sz[u]-1);
            int v=query(u).ans;
            if(v>=0)seg.update(disc[u],-v-1);
        }else cout << (query(u).ans<0?"white":"black") << "\n";
    }
}