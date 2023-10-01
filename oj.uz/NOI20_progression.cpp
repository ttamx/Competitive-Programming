#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;

const int N=3e5+5;
const int K=1<<20;

int n,q;
ll a[N],b[N];

struct segtree{
    struct node{
        ll sz,ans,all,sum;
        p2 pre,suf;
        node(ll x=0):sz(1),pre(p2(1,x)),suf(p2(1,x)),all(1),ans(1),sum(x){}
        friend node operator+(node a,node b){
            node c;
            bool ok=(a.suf.second==b.pre.second);
            bool oka=(a.suf.first==a.sz);
            bool okb=(b.pre.first==b.sz);
            c.sz=a.sz+b.sz;
            c.sum=a.sum+b.sum;
            if(ok&&oka){
                c.pre=b.pre;
                c.pre.first+=a.sz;
            }else{
                c.pre=a.pre;
            }
            if(ok&&okb){
                c.suf=a.suf;
                c.suf.first+=b.sz;
            }else{
                c.suf=b.suf;
            }
            if(ok&&oka&&okb){
                c.all=a.sz+b.sz;
            }else{
                c.all=0;
            }
            c.ans=max(a.ans,b.ans);
            if(ok){
                c.ans=max(c.ans,a.suf.first+b.pre.first);
            }
            return c;
        }
    }t[K];
    ll lz[K];
    bool islz[K];
    void pushlz(int l,int r,int i){
        if(islz[i]){
            t[i].all=t[i].ans=t[i].sz;
            t[i].sum=t[i].sz*lz[i];
            t[i].pre=t[i].suf=p2(t[i].sz,lz[i]);
            if(l<r){
                lz[i*2]=lz[i*2+1]=lz[i];
                islz[i*2]=islz[i*2+1]=true;
            }
        }else{
            t[i].sum+=t[i].sz*lz[i];
            t[i].pre.second+=lz[i];
            t[i].suf.second+=lz[i];
            if(l<r){
                lz[i*2]+=lz[i];
                lz[i*2+1]+=lz[i];
            }
        }
        lz[i]=0;
        islz[i]=false;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=b[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n+1,1);
    }
    void update(int l,int r,int i,int x,int y,ll v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,pushlz(l,r,i),void();
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,ll v){
        update(1,n+1,1,x,y,v);
    }
    void update2(int l,int r,int i,int x,int y,ll v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return islz[i]=true,lz[i]=v,pushlz(l,r,i),void();
        int m=(l+r)/2;
        update2(l,m,i*2,x,y,v);
        update2(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update2(int x,int y,ll v){
        update2(1,n+1,1,x,y,v);
    }
    node query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        if(x<=m&&m<y)return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
        if(x<=m)return query(l,m,i*2,x,y);
        else return query(m+1,r,i*2+1,x,y);
    }
    node query(int x,int y){
        return query(1,n+1,1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)b[i]=a[i]-a[i-1];
    s.build();
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            ll l,r,a,b;
            cin >> l >> r >> a >> b;
            s.update(l,l,a);
            s.update(l+1,r,b);
            s.update(r+1,r+1,-a-(r-l)*b);
        }else if(t==2){
            ll l,r,a,b;
            cin >> l >> r >> a >> b;
            ll le=(l==1?0:s.query(1,l-1).sum);
            ll ri=s.query(1,r+1).sum;
            s.update2(l,l,a-le);
            s.update2(r+1,r+1,ri-a-(r-l)*b);
            s.update2(l+1,r,b);
        }else{
            ll l,r;
            cin >> l >> r;
            cout << (l==r?0:s.query(l+1,r).ans)+1 << "\n";
        }
    }
}