#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll N=1e5+5;
const ll K=1<<18;

ll n,q;
ll a[N];

struct segtree{
    ll s[K],lz1[K],lz2[K],lz3[K];
    void pushlz1(ll l,ll r,ll i){
        if(lz1[i]==0)return;
        if(l<r){
            lz1[i*2]+=lz1[i];
            lz1[i*2+1]+=lz1[i];
        }else{
            s[i]+=lz1[i];
        }
        lz1[i]=0;
    }
    void pushlz2(ll l,ll r,ll i){
        if(lz2[i]==0)return;
        if(l<r){
            lz2[i*2]+=lz2[i];
            lz2[i*2+1]+=lz2[i];
            ll m=(l+r)/2;
            ll sz=m-l+1;
            lz1[i*2+1]+=sz*lz2[i];
        }else{
            s[i]+=lz2[i];
        }
        lz2[i]=0;
    }
    void pushlz3(ll l,ll r,ll i){
        if(lz3[i]==0)return;
        if(l<r){
            lz3[i*2]+=lz3[i];
            lz3[i*2+1]+=lz3[i];
            ll m=(l+r)/2;
            ll sz=r-m;
            lz1[i*2]+=sz*lz3[i];
        }else{
            s[i]+=lz3[i];
        }
        lz3[i]=0;
    }
    void pushall(ll l,ll r,ll i){
        pushlz1(l,r,i);
        pushlz2(l,r,i);
        pushlz3(l,r,i);
    }
    void build(ll l,ll r,ll i){
        if(l==r){
            s[i]=a[l];
            return;
        }
        ll m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void update1(ll l,ll r,ll i,ll x,ll y,ll v){
        pushall(l,r,i);
        if(y<l||x>r)return;
        if(x<=l&&r<=y){
            lz1[i]+=v;
            pushall(l,r,i);
            return;
        }
        ll m=(l+r)/2;
        update1(l,m,i*2,x,y,v);
        update1(m+1,r,i*2+1,x,y,v);
    }
    void update2(ll l,ll r,ll i,ll x,ll y,ll v){
        pushall(l,r,i);
        if(y<l||x>r)return;
        if(x<=l&&r<=y){
            lz2[i]+=v;
            pushall(l,r,i);
            return;
        }
        ll m=(l+r)/2;
        if(x<=m+1&&m+1<=y)update1(m+1,r,i*2+1,x,y,m-max(l,x)+1);
        update2(l,m,i*2,x,y,v);
        update2(m+1,r,i*2+1,x,y,v);
    }
    void update3(ll l,ll r,ll i,ll x,ll y,ll v){
        pushall(l,r,i);
        if(y<l||x>r)return;
        if(x<=l&&r<=y){
            lz3[i]+=v;
            pushall(l,r,i);
            return;
        }
        ll m=(l+r)/2;
        if(x<=m&&m<=y)update1(l,m,i*2,x,y,min(r,y)-m);
        update3(l,m,i*2,x,y,v);
        update3(m+1,r,i*2+1,x,y,v);
    }
    ll query(ll l,ll r,ll i,ll x){
        pushall(l,r,i);
        if(x<l||r<x)return 0;
        if(l==r)return s[i];
        ll m=(l+r)/2;
        return query(l,m,i*2,x)+query(m+1,r,i*2+1,x);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(ll i=1;i<=n;i++){
        cin >> a[i];
    }
    seg.build(1,n,1);
    while(q--){
        ll o;
        cin >> o;
        if(o==1){
            ll l,r,w;
            cin >> l >> r >> w;
            seg.update1(1,n,1,l,r,w);
            if(w<2)continue;
            if(l>1){
                if(l-w+1>0){
                    seg.update2(1,n,1,l-w+1,l-1,1);
                }else{
                    seg.update1(1,n,1,1,l-1,w-l);
                    seg.update2(1,n,1,1,l-1,1);
                }
            }
            if(r<n){
                if(r+w-1<=n){
                    seg.update3(1,n,1,r+1,r+w-1,1);
                }else{
                    seg.update1(1,n,1,r+1,n,r+w-n-1);
                    seg.update3(1,n,1,r+1,n,1);
                }
            }
        }else{
            ll x;
            cin >> x;
            ll tmp=seg.query(1,n,1,x);
            cout << tmp << '\n';
            seg.update1(1,n,1,x,x,-tmp);
        }
    }
}