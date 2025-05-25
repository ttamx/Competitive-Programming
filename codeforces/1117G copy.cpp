#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+6;
const int K=1<<21;

int n,q;
int a[N];
int ql[N],qr[N];
vector<int> queries[N];
ll ans[N];

struct MaxSegtree{
    int t[K];
    int merge(int l,int r){
        return a[l]>a[r]?l:r;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=l);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=merge(t[i*2],t[i*2+1]);
    }
    void build(){
        build(1,n,1);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return merge(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg_max;

struct LazySegtree{
    ll t[K],lz[K];
    void push(int l,int r,int i){
        t[i]+=(r-l+1)*lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0LL;
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
    void update(int l,int r,int i,int x,int y,ll v){
        push(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]+=v,push(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,ll v){
        update(1,n,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        push(l,r,i);
        if(y<l||r<x)return 0LL;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

void rec_l(int l,int r){
    if(l>r)return;
    int m=seg_max.query(l,r);
    rec_l(l,m-1);
    rec_l(m+1,r);
    for(auto i:queries[m]){
        ans[i]+=seg.query(ql[i],m);
    }
    seg.update(m,m,r-m+1);
    if(l<m)seg.update(l,m-1,1);
}

void rec_r(int l,int r){
    if(l>r)return;
    int m=seg_max.query(l,r);
    rec_r(l,m-1);
    rec_r(m+1,r);
    for(auto i:queries[m]){
        ans[i]+=seg.query(m,qr[i]);
    }
    seg.update(m,m,m-l+1);
    if(r>m)seg.update(m+1,r,1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=q;i++){
        cin >> ql[i];
    }
    for(int i=1;i<=q;i++){
        cin >> qr[i];
    }
    seg_max.build();
    for(int i=1;i<=q;i++){
        ans[i]=qr[i]-ql[i]+1;
        queries[seg_max.query(ql[i],qr[i])].emplace_back(i);
    }
    rec_l(1,n);
    seg.build();
    rec_r(1,n);
    for(int i=1;i<=q;i++){
        cout << ans[i] << " \n"[i==q];
    }
}