#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e4+4;
const int K=1<<17;
const int mod=1e9+7;

int n,q;
ll a[N];

struct segtree{
    ll t1[K],t2[K],lz[K];
    void pushlz(int l,int r,int i){
        int sz=r-l+1;
        t2[i]+=(2ll*t1[i]+lz[i]*sz)%mod*lz[i]%mod;
        t2[i]%=mod;
        t1[i]+=sz*lz[i]%mod;
        t1[i]%=mod;
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2]%=mod;
            lz[i*2+1]+=lz[i];
            lz[i*2+1]%=mod;
        }
        lz[i]=0;
    }
    void build(int l,int r,int i){
        if(l==r)return t1[i]=a[l],t2[i]=a[l]*a[l]%mod,void();
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t1[i]=(t1[i*2]+t1[i*2+1])%mod;
        t2[i]=(t2[i*2]+t2[i*2+1])%mod;
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
        t1[i]=(t1[i*2]+t1[i*2+1])%mod;
        t2[i]=(t2[i*2]+t2[i*2+1])%mod;
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return 0ll;
        if(x<=l&&r<=y)return t2[i];
        int m=(l+r)/2;
        return (query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y))%mod;
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    s.build();
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int l,r,c;
            cin >> l >> r >> c;
            s.update(l,r,c);
        }else{
            int l,r;
            cin >> l >> r;
            cout << s.query(l,r) << "\n";
        }
    }
}