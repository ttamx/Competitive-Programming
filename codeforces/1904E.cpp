#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

const int N=2e5+5;
const int K=1<<19;

int n,q;
vi adj[N];
int tin[N],tout[N],dist[N],lv[N];
int timer=0;
vi qr[N],a[N];
int b[N],ans[N],path[N];

struct segtree{
    ll t[K];
    ll lz[K];
    void pushlz(int l,int r,int i){
        if(!lz[i])return;
        t[i]+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=dist[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,int v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,pushlz(l,r,i),void();
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    int query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return -1;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}s;

void predfs(int u,int p=0,int d=0){
    tin[u]=++timer;
    dist[timer]=d;
    lv[u]=d;
    for(auto v:adj[u])if(v!=p)predfs(v,u,d+1);
    tout[u]=timer;
}

void dfs(int u,int p=0){
    path[lv[u]]=u;
    for(auto i:qr[u]){
        for(auto v:a[i]){
            if(lv[v]<lv[u]&&path[lv[v]]==v){
                int w=path[lv[v]+1];
                s.update(1,n,-INF);
                s.update(tin[w],tout[w],INF);
            }else{
                s.update(tin[v],tout[v],-INF);
            }
        }
        ans[i]=max(0ll,s.t[1]);
        for(auto v:a[i]){
            if(lv[v]<lv[u]&&path[lv[v]]==v){
                int w=path[lv[v]+1];
                s.update(1,n,INF);
                s.update(tin[w],tout[w],-INF);
            }else{
                s.update(tin[v],tout[v],INF);
            }
        }
    }
    for(auto v:adj[u])if(v!=p){
        s.update(1,n,1);
        s.update(tin[v],tout[v],-2);
        dfs(v,u);
        s.update(1,n,-1);
        s.update(tin[v],tout[v],2);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=q;i++){
        int x,k;
        cin >> x >> k;
        a[i].resize(k);
        bool ok=true;
        for(auto &y:a[i]){
            cin >> y;
            if(y==x)ok=false;
        }
        if(ok)qr[x].emplace_back(i);
    }
    predfs(1);
    s.build();
    dfs(1);
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}