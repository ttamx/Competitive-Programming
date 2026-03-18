#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=250005;
const int K=1<<19;
const int INF=INT_MAX/2;

int n,q;
int a[N],b[N];
vector<int> adj[N];
int sz[N],par[N],dep[N],hv[N],hd[N],disc[N],pos[N];
int timer=0;

struct Info{
    int mn,cnt;
    Info():mn(INF),cnt(0){}
    Info(int v):mn(v),cnt(1){}
    friend Info operator+(const Info &l,const Info &r){
        Info res;
        res.mn=min(l.mn,r.mn);
        if(res.mn==l.mn)res.cnt+=l.cnt;
        if(res.mn==r.mn)res.cnt+=r.cnt;
        return res;
    }
};

struct Tag{
    int flip,add;
    void apply(const Tag &o){
        if(o.flip){
            flip^=1;
            add*=-1;
        }
        add+=o.add;
    }
};

struct Segtree{
    Info t[K][4];
    Tag lz[K];
    void apply(int i,const Tag &v){
        if(v.flip){
            swap(t[i][0],t[i][2]);
            swap(t[i][1],t[i][3]);
            swap(t[i][0],t[i][1]);
            swap(t[i][2],t[i][3]);
        }
        t[i][0].mn-=v.add;
        t[i][1].mn+=v.add;
        t[i][2].mn-=v.add;
        t[i][3].mn+=v.add;
        lz[i].apply(v);
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=Tag{0,0};
    }
    void pull(int i){
        t[i][0]=t[i*2][0]+t[i*2+1][0];
        t[i][1]=t[i*2][1]+t[i*2+1][1];
        t[i][2]=t[i*2][2]+t[i*2+1][2];
        t[i][3]=t[i*2][3]+t[i*2+1][3];
    }
    void build(int l,int r,int i){
        lz[i]=Tag{0,0};
        if(l==r){
            int u=pos[l];
            t[i][a[u]]=Info(b[u]);
            t[i][a[u]^2]=Info(sz[u]-b[u]);
            t[i][a[u]^1]=t[i][a[u]^3]=Info();
            return;
        }
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        pull(i);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,const Tag &v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void update(int x,int y,const Tag &v){
        update(1,n,1,x,y,v);
    }
    void dbg(int l,int r,int i){
        if(l==r){
            cerr << pos[l] << ": " << (t[i][1].mn<INF?t[i][1].mn:-9) << " " << (t[i][0].mn<INF?t[i][0].mn:-9) << "\n";
            return;
        }
        push(i);
        int m=(l+r)/2;
        dbg(l,m,i*2);
        dbg(m+1,r,i*2+1);
    }
    void dbg(){
        dbg(1,n,1);
        cerr << "\n";
    }
}seg;

struct Segtree2{
    int t[K][2];
    int lz[K];
    void apply(int i,int v){
        if(v)swap(t[i][0],t[i][1]);
        lz[i]^=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void pull(int i){
        t[i][0]=t[i*2][0]+t[i*2+1][0];
        t[i][1]=t[i*2][1]+t[i*2+1][1];
    }
    void build(int l,int r,int i){
        lz[i]=0;
        if(l==r){
            int u=pos[l];
            t[i][a[u]]=1;
            t[i][a[u]^1]=0;
            return;
        }
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        pull(i);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i][1];
        push(i);
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg2;

void dfs(int u){
    sz[u]=1;
    b[u]=a[u];
    for(auto v:adj[u]){
        if(v==par[u])continue;
        par[v]=u;
        dep[v]=dep[u]+1;
        dfs(v);
        b[u]+=b[v];
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u){
    disc[u]=++timer;
    pos[timer]=u;
    if(!hd[u])hd[u]=u;
    if(hv[u])hd[hv[u]]=hd[u],hld(hv[u]);
    for(auto v:adj[u])if(v!=par[u]&&v!=hv[u])hld(v);
}

void answer(){
    Info res=seg.t[1][1];
    if(res.mn==1){
        cout << res.cnt << "\n";
    }else{
        cout << 0 << "\n";
    }
}

void runcase(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    hld(1);
    seg.build();
    seg2.build();
    cin >> q;
    // seg.dbg();
    answer();
    while(q--){
        int u;
        cin >> u;
        int l=disc[u],r=disc[u]+sz[u]-1;
        seg.update(l,r,Tag{1,0});
        int dif=sz[u]-2*seg2.query(l,r);
        seg2.update(l,r,1);
        u=par[u];
        while(u){
            seg.update(disc[hd[u]],disc[u],Tag{0,dif});
            u=par[hd[u]];
        }
        // seg.dbg();
        answer();
    }
    for(int i=1;i<=n;i++){
        adj[i].clear();
        a[i]=b[i]=sz[i]=par[i]=dep[i]=hv[i]=hd[i]=disc[i]=pos[i]=0;
    }
    timer=0;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}