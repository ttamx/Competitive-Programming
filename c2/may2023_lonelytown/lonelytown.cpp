#include "lonelytown.h"
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;
typedef tuple<int,int,int> t3;

const int N=1e5+5;
const int K=1<<18;
const int inf=1e9;

int n,q;
int a[N];
multiset<int> msl[N];
multiset<int,greater<int>> msr[N];

struct segtree{
    p2 t[K];
    int lz[K];
    p2 merge(p2 l,p2 r){
        if(l.first<r.first)return l;
        if(l.first>r.first)return r;
        return {l.first,l.second+r.second};
    }
    void pushlz(int l,int r,int i){
        t[i].first+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]={0,1});
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=merge(t[i*2],t[i*2+1]);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int &x,int &y,int &v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,pushlz(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=merge(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    p2 query(int l,int r,int i,int &x,int &y){
        pushlz(l,r,i);
        if(y<l||r<x)return p2(inf,0);
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return merge(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    p2 query(int x,int y){
        return query(1,n,1,x,y);
    }
}s;

struct minsegtree{
    int t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=inf);
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
    int find(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x||t[i]>v)return n+1;
        if(l==r)return l;
        int m=(l+r)/2;
        int p=find(l,m,i*2,x,y,v);
        if(p>n)p=find(m+1,r,i*2+1,x,y,v);
        return p;
    }
    int find(int x,int y,int v){
        return find(1,n,1,x,y,v);
    }
}sl;

struct maxsegtree{
    int t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=-inf);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=max(t[i*2],t[i*2+1]);
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
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int v){
        update(1,n,1,x,v);
    }
    int find(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x||t[i]<v)return 0;
        if(l==r)return l;
        int m=(l+r)/2;
        int p=find(m+1,r,i*2+1,x,y,v);
        if(p<1)p=find(l,m,i*2,x,y,v);
        return p;
    }
    int find(int x,int y,int v){
        return find(1,n,1,x,y,v);
    }
}sr;

struct fenwick{
    int t[N];
    void add(int i,int v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

void addedge(int l,int r){
    if(l>r)swap(l,r);
    s.update(l,r,1);
    msl[r].emplace(l);
    msr[l].emplace(r);
    sl.update(r,*msl[r].begin());
    sr.update(l,*msr[l].begin());
    f.add(l,1);
    f.add(r,-1);
}

void deledge(int l,int r){
    if(l>r)swap(l,r);
    s.update(l,r,-1);
    msl[r].erase(msl[r].find(l));
    msr[l].erase(msr[l].find(r));
    sl.update(r,*msl[r].begin());
    sr.update(l,*msr[l].begin());
    f.add(l,-1);
    f.add(r,1);
}

void init_town(int N, int Q, vector<int> u, vector<int> v) {
    n=N,q=Q;
    for(int i=1;i<=n;i++){
        msl[i].emplace(inf);
        msr[i].emplace(-inf);
    }
    s.build();
    sl.build();
    sr.build();
    for(int i=0;i<n-1;i++)addedge(u[i]+1,v[i]+1);
}

void change_edge(int x, int y, int z) {
    x++,y++,z++;
    deledge(x,y);
    addedge(x,z);
}

int lonelytown_query() {
    auto [x,y]=s.query(1,n);
    return x==0?y:0;
}

int simulate_query(int e) {
    e++;
    int cnt=f.read(e);
    if(cnt==0)return lonelytown_query();
    int l=sr.find(1,e,e+1);
    int r=sl.find(e+1,n,e);
    if(cnt==1){
        deledge(l,r);
        int res=lonelytown_query();
        addedge(l,r);
        return res;
    }
    auto calc=[&](int l,int r,int v){
        auto [x,y]=s.query(l,r);
        return x==v?y:0;
    };
    return calc(1,l,0)+calc(l+1,r-1,cnt)+calc(r,n,0);
}