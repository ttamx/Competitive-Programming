#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

using ll = long long;

const int N=2e6+5;
const int K=1<<22;
const ll INF=1e18;

ll m,k;
int n,q;
ll a[N];
vector<tuple<ll,ll,int>> qr;
int ans[N];

struct Segtree{
    struct Line{
        ll m,c;
        ll eval(ll x)const{
            return m*x+c;
        }
    }t[K];
    ll p[K];
    ll cur;
    inline bool cmp(const Line &x,const Line &y)const{
        ll vx=x.eval(cur);
        ll vy=y.eval(cur);
        return vx<vy||(vx==vy&&x.m<y.m);
    }
    inline ll isect(const Line &x,const Line &y)const{
        if(x.m<=y.m)return INF;
        ll d=y.eval(cur)-x.eval(cur);
        ll res=cur+(d-1)/(x.m-y.m)+1;
        return res>cur?res:INF;
    }
    inline void work(int l,int r,int i){
        if(l==r||p[i]>cur)return;
        int m=(l+r)/2;
        work(l,m,i*2);
        work(m+1,r,i*2+1);
        auto x=t[i*2];
        auto y=t[i*2+1];
        if(!cmp(x,y))swap(x,y);
        t[i]=x;
        p[i]=min({p[i*2],p[i*2+1],isect(x,y)});
    }
    inline void build(int l,int r,int i){
        if(l==r){
            t[i]=Line{-l,a[l]};
            p[i]=INF;
            return;
        }
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        work(l,r,i);
    }
    inline void build(){
        build(1,n,1);
    }
    inline ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return INF;
        if(x<=l&&r<=y)return t[i].eval(cur);
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    inline ll query(int x,int y){
        return query(1,n,1,x,y);
    }
    inline pair<int,ll> find_last(int l,int r,int i,int x,int y,ll tar,ll v){
        if(y<l||r<x)return {-1,v};
        ll tmp=min(t[i].eval(cur),v);
        if(x<=l&&r<=y&&tmp+(l-1)*cur>=tar)return {-1,tmp};
        if(l==r)return {l,INF};
        int m=(l+r)/2;
        auto [res,vv]=find_last(m+1,r,i*2+1,x,y,tar,v);
        if(res!=-1)return {res,vv};
        return find_last(l,m,i*2,x,y,tar,vv);
    }
    inline int find_last(int x,int y,ll k){
        return find_last(1,n,1,x,y,k,INF).first;
    }
    inline void heaten(ll x){
        cur=x;
        work(1,n,1);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n >> k >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=q;i++){
        ll x,y;
        cin >> x >> y;
        qr.emplace_back(x,y,i);
    }
    seg.build();
    sort(qr.begin(),qr.end());
    for(auto [x,y,i]:qr){
        seg.heaten(x);
        int l=lower_bound(a+1,a+n+1,y-k)-a;
        int r=upper_bound(a+1,a+n+1,y)-a-1;
        ans[i]=r-max(seg.find_last(l,r,y-k),l-1);
    }
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}