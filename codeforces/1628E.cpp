#include<bits/stdc++.h>

using namespace std;

const int N=300005;
const int K=1<<20;
const int INF=INT_MAX/2;

int n,q,cur;
vector<tuple<int,int,int>> e;
int fa[N*2],par[N*2],l[N*2],r[N*2],a[N*2],disc[N*2],hv[N*2],hd[N*2],dep[N*2],id[N*2];
int timer;

int fp(int u){return fa[u]=u==fa[u]?u:fp(fa[u]);}

int dfs(int u){
    if(!u)return 0;
    dep[u]=dep[par[u]]+1;
    disc[u]=++timer;
    id[timer]=u;
    int sl=dfs(l[u]),sr=dfs(r[u]);
    hv[u]=sl>sr?l[u]:r[u];
    return sl+sr+1;
}

void hld(int u){
    if(!u)return;
    if(!hd[u])hd[u]=u;
    hd[hv[u]]=hd[u];
    hld(hv[u]);
    hld(hv[u]^l[u]^r[u]);
}

int lca(int u,int v){
    while(hd[u]!=hd[v]){
        if(dep[hd[u]]<dep[hd[v]])swap(u,v);
        u=par[hd[u]];
    }
    return dep[u]<dep[v]?u:v;
}

struct Info{
    int mn,mx;
    Info():mn(INF),mx(-INF){}
    Info(int _mn,int _mx):mn(_mn),mx(_mx){}
    friend Info operator+(const Info &l,const Info &r){return Info(min(l.mn,r.mn),max(l.mx,r.mx));}
};

struct Segtree{
    struct Node{
        Info val,mem;
        Node():val(),mem(){}
        Node(Info _val,Info _mem):val(_val),mem(_mem){}
        friend Node operator+(const Node &l,const Node &r){return Node(l.val+r.val,l.mem+r.mem);}
    }t[K];
    int lz[K];
    void apply(int i,int v){
        t[i].val=v?t[i].mem:Info();
        lz[i]=v;
    }
    void push(int i){
        if(lz[i]==-1)return;
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=-1;
    }
    void build(int l,int r,int i){
        lz[i]=-1;
        if(l==r)return void(t[i].mem.mn=t[i].mem.mx=disc[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){build(1,n,1);}
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        int m=(l+r)/2;
        push(i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,int v){update(1,n,1,x,y,v);}
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    e.resize(n-1);
    for(auto &[w,u,v]:e)cin >> u >> v >> w;
    sort(e.begin(),e.end());
    cur=n;
    iota(fa+1,fa+n*2+1,1);
    for(auto [w,u,v]:e){
        cur++;
        u=fp(u),v=fp(v);
        fa[u]=fa[v]=par[u]=par[v]=cur;
        l[cur]=u,r[cur]=v;
        a[cur]=w;
    }
    dfs(cur);
    hld(cur);
    seg.build();
    while(q--){
        int t;
        cin >> t;
        if(t==3){
            int x;
            cin >> x;
            auto res=seg.t[1].val;
            if(res.mn>res.mx){
                cout << -1 << "\n";
                continue;
            }
            int v=lca(id[res.mn],id[res.mx]);
            int ans=a[lca(x,v)];
            cout << (ans?ans:-1) << "\n";
        }else{
            int l,r;
            cin >> l >> r;
            seg.update(l,r,2-t);
        }
    }
}