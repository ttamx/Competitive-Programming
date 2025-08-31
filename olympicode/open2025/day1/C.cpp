#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int K=1<<21;

int n,q;
int a[N];
vector<tuple<int,int,int>> qr[N];
int ans[N];

struct Segtree{
    pair<int,int> t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=make_pair(a[l],l));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void build(){
        build(1,n,1);
    }
    pair<int,int> query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return make_pair(0,0);
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    pair<int,int> query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

struct Segtree2{
    int t[K],lz[K];
    void apply(int i,int v){
        t[i]+=v;
        lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        int m=(l+r)/2;
        push(i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        push(i);
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}segl,segr;

void dnc(int l,int r){
    if(l>r)return;
    int m=seg.query(l,r).second;
    dnc(l,m-1);
    dnc(m+1,r);
    for(auto [li,ri,i]:qr[m]){
        ans[i]=max(segl.query(li,m-1),segr.query(m+1,ri));
    }
    int dpl=segl.query(l,m-1)+1;
    int dpr=segr.query(m+1,r)+1;
    segl.update(m,m,dpr);
    segl.update(l,m-1,1);
    segr.update(m,m,dpl);
    segr.update(m+1,r,1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    seg.build();
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[seg.query(l,r).second].emplace_back(l,r,i);
    }
    dnc(1,n);
    for(int i=1;i<=q;i++){
        cout << ans[i] << "\n"; 
    }
}