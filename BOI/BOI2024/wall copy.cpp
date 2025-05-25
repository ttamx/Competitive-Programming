#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int MOD=1e9+7;

int n;
ll a[N],b[N];
ll pw[N]; 
ll ans;

struct Segtree{
    ll t[N],lz[N];
    void apply(int i,ll v){
        t[i]=(t[i]*v)%MOD;
        lz[i]=(lz[i]*v)%MOD;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=1;
    }
    void build(int l,int r,int i){
        t[i]=lz[i]=1;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
    }
    void update(int x,int y,ll v){
        update(1,n,1,x,y,v);
    }
    ll query(int l,int r,int i,int x){
        if(l==r)return t[i];
        push(i);
        int m=(l+r)/2;
        if(x<=m)return query(l,m,i*2,x);
        return query(m+1,r,i*2+1,x);
    }
    ll query(int x){
        return query(1,n,1,x);
    }
}s;

ll vla[N],vra[N],vlb[N],vrb[N];

ll subtract(){
    ll sum=0;
    s.build();
    for(int i=1;i<=n;i++){
        vla[i]=s.query(a[i]);
        vlb[i]=s.query(b[i]);
        s.update(1,a[i]-1,0LL);
        s.update(a[i],b[i]-1,1LL);
        s.update(b[i],n,2LL);
    }
    s.build();
    for(int i=n;i>=1;i--){
        vra[i]=s.query(a[i]);
        vrb[i]=s.query(b[i]);
        s.update(1,a[i]-1,0LL);
        s.update(a[i],b[i]-1,1LL);
        s.update(b[i],n,2LL);
    }
    for(int i=2;i<=n-1;i++){
        sum+=(MOD+pw[i-1]-vla[i])*(MOD+pw[n-i]-vra[i])%MOD*a[i]%MOD;
        sum+=(MOD+pw[i-1]-vlb[i])*(MOD+pw[n-i]-vrb[i])%MOD*b[i]%MOD;
        sum%=MOD;
    }
    cerr << sum << "\n";
    return sum;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    for(int i=1;i<=n;i++)if(a[i]>b[i])swap(a[i],b[i]);
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%MOD;
    ans+=MOD-subtract();
    ans%=MOD;
    cout << ans;
}