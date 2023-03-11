#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int K=1<<20;

int n,k;

struct segtree{
    ll t[K],lz[K];
    void pushlz(int l,int r,int i){
        t[i]+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=(l>0?1e18:0));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void build(){
        build(0,k,1);
    }
    void update(int l,int r,int i,int &x,int &y,ll &v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y){
            lz[i]+=v;
            pushlz(l,r,i);
            return;
        }
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,ll v){
        update(0,k,1,x,y,v);
    }
    void singleupd(int l,int r,int i,int &x,ll &v){
        pushlz(l,r,i);
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=min(t[i],v));
        int m=(l+r)/2;
        singleupd(l,m,i*2,x,v);
        singleupd(m+1,r,i*2+1,x,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void singleupd(int x,ll v){
        singleupd(0,k,1,x,v);
    }
    ll query(int l,int r,int i,int &x,int &y){
        pushlz(l,r,i);
        if(y<l||r<x)return 1e18;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    ll query(int x,int y){
        return query(0,k,1,x,y);
    }
}s;

void runcase(){
    cin >> n >> k;
    s.build();
    vector<ll> a(n+1),h(k+1),c(k+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=k;i++)cin >> c[i];
    for(int i=1;i<=k;i++)cin >> h[i];
    for(int i=1;i<=n;i++){
        if(a[i]==a[i-1]){
            ll mn=s.query(0,k);
            ll val=s.query(a[i],a[i]);
            s.update(0,k,h[a[i]]);
            s.singleupd(a[i],min(mn+c[a[i]],val+h[a[i]]));
        }else{
            ll mn=s.query(0,k);
            ll val=s.query(a[i],a[i]);
            s.update(0,k,c[a[i]]);
            s.singleupd(a[i-1],min(mn+c[a[i]],val+h[a[i]]));
        }
    }
    cout << s.query(0,k) << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}