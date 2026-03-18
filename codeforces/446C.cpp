#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3e5+5;
const int K=1<<20;
const int MOD=1e9+9;

int n,q;
int a[N];
ll ca[N],cb[N],sa[N],sb[N];

struct Tag{
    ll a,b;
    void shift(int d){
        tie(a,b)=make_pair((a*ca[d]+b*cb[d])%MOD,(a*ca[d+1]+b*cb[d+1])%MOD);
    }
};

struct Segtree{
    ll t[K];
    Tag lz[K];
    void apply(int l,int r,int i,Tag v,int st){
        v.shift(l-st);
        t[i]=(t[i]+v.a*sa[r-l]+v.b*sb[r-l])%MOD;
        lz[i].a=(lz[i].a+v.a)%MOD;
        lz[i].b=(lz[i].b+v.b)%MOD;
    }
    void push(int l,int m,int r,int i){
        apply(l,m,i*2,lz[i],l);
        apply(m+1,r,i*2+1,lz[i],l);
        lz[i]=Tag{0,0};
    }
    void pull(int i){
        t[i]=(t[i*2]+t[i*2+1])%MOD;
    }
    void build(int l,int r,int i){
        lz[i]=Tag{0,0};
        if(l==r)return void(t[i]=a[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        pull(i);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,Tag v,int st){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,i,v,st);
        int m=(l+r)/2;
        push(l,m,r,i);
        update(l,m,i*2,x,y,v,st);
        update(m+1,r,i*2+1,x,y,v,st);
        pull(i);
    }
    void update(int x,int y,Tag v){
        update(1,n,1,x,y,v,x);
    }
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0LL;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        push(l,m,r,i);
        return (query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y))%MOD;
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;


int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    ca[0]=1;
    cb[1]=1;
    for(int i=2;i<n;i++){
        ca[i]=(ca[i-1]+ca[i-2])%MOD;
        cb[i]=(cb[i-1]+cb[i-2])%MOD;
    }
    for(int i=0;i<n;i++){
        sa[i]=(ca[i]+(i?sa[i-1]:0LL))%MOD;
        sb[i]=(cb[i]+(i?sb[i-1]:0LL))%MOD;
    }
    seg.build();
    while(q--){
        int op,l,r;
        cin >> op >> l >> r;
        if(op==1){
            seg.update(l,r,Tag{1,1});
        }else{
            cout << seg.query(l,r) << "\n";
        }
    }
}