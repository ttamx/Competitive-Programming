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
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

const int K=1<<20;

int n;

struct segtree{
    ll t[K],lz[K];
    void push(int l,int r,int i){
        t[i]+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void build(int l,int r,int i){
        t[i]=lz[i]=0;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,const ll &v){
        push(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]+=v,push(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,const ll &v){
        update(1,n,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        push(l,r,i);
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
}s;

void runcase(){
    cin >> n;
    s.build();
    vi a(n),tin(n),tout(n);
    vector<vi> adj(n),col(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        p--;
        adj[p].emplace_back(i);
    }
    for(auto &x:a)cin >> x,x--;
    int timer=0;
    function<void(int)> tour=[&](int u){
        tin[u]=++timer;
        for(auto v:adj[u])tour(v);
        tout[u]=timer;
    };
    tour(0);
    ll ans=1;
    function<void(int)> solve=[&](int u){
        col[a[u]].emplace_back(u);
        for(auto v:adj[u])solve(v);
        while(col[a[u]].back()!=u){
            int v=col[a[u]].back();
            s.update(tin[v],tout[v],-1);
            col[a[u]].pop_back();
        }
        s.update(tin[u],tout[u],1);
        pll mx(1,-LINF);
        auto upd=[&](ll x){
            mx.second=max(mx.second,x);
            if(mx.first<mx.second)swap(mx.first,mx.second);
        };
        for(auto v:adj[u])upd(s.query(tin[v],tout[v]));
        ans=max(ans,mx.first*mx.second);
    };
    solve(0);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}