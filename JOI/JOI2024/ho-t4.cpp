#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int Q=2e5+5;
const int K=(1<<21)+5;

int n,q;
int a[N],b[N];
int l[N],r[N];
vector<pair<int,int>> qr[N];
vector<int> upd[N];
bool ans[Q];

struct maxsegtree{
    int t[K],lz[K];
    void push(int l,int r,int i){
        t[i]=max(t[i],lz[i]);
        if(l<r){
            lz[i*2]=max(lz[i*2],lz[i]);
            lz[i*2+1]=max(lz[i*2+1],lz[i]);
        }
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,int v){
        push(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,push(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(1,n*2,1,x,y,v);
    }
    int query(int l,int r,int i,int x,int y){
        push(l,r,i);
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n*2,1,x,y);
    }
}sl;

struct minsegtree{
    int t[K],lz[K];
    void push(int l,int r,int i){
        t[i]=min(t[i],lz[i]);
        if(l<r){
            lz[i*2]=min(lz[i*2],lz[i]);
            lz[i*2+1]=min(lz[i*2+1],lz[i]);
        }
        lz[i]=n+1;
    }
    void build(int l,int r,int i){
        t[i]=lz[i]=n+1;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(1,n*2,1);
    }
    void update(int l,int r,int i,int x,int y,int v){
        push(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,push(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(1,n*2,1,x,y,v);
    }
    int query(int l,int r,int i,int x,int y){
        push(l,r,i);
        if(y<l||r<x)return n+1;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n*2,1,x,y);
    }
}sr;

struct segtree{
    int t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=::l[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int v){
        update(1,n,1,x,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return n+1;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    cin >> q;
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[r].emplace_back(l,i);
    }
    for(int i=1;i<=n;i++){
        l[i]=sl.query(b[i],a[i]);
        sl.update(b[i],a[i],i);
    }
    sr.build();
    for(int i=n;i>=1;i--){
        r[i]=sr.query(b[i],a[i]);
        sr.update(b[i],a[i],i);
    }
    for(int i=1;i<=n;i++){
        upd[r[i]].emplace_back(i);
    }
    s.build();
    for(int i=1;i<=n;i++){
        for(auto j:upd[i]){
            s.update(j,n+1);
        }
        for(auto [ql,j]:qr[i]){
            ans[j]=s.query(ql,i)>=ql;
        }
    }
    for(int i=1;i<=q;i++)cout << (ans[i]?"Yes":"No") << "\n";
}