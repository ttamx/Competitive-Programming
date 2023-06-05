#include "lonelytown.h"
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1e5+5;
const int K=1<<18;

int n,q;

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
    void build(int l,int r,int i,vector<int> &a){
        if(l==r)return void(t[i]={a[l],1});
        int m=(l+r)/2;
        build(l,m,i*2,a);
        build(m+1,r,i*2+1,a);
        t[i]=merge(t[i*2],t[i*2+1]);
    }
    void build(vector<int> a){
        build(0,n-1,1,a);
    }
    void update(int l,int r,int i,int &x,int &y,int &v){
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
        t[i]=merge(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(0,n-1,1,x,y,v);
    }
    p2 query(int l,int r,int i,int &x,int &y){
        pushlz(l,r,i);
        if(y<l||r<x)return {INT_MAX,0};
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return merge(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    p2 query(int x,int y){
        return query(0,n-1,1,x,y);
    }
}s;

void init_town(int N, int Q, vector<int> u, vector<int> v) {
    n=N,q=Q;
    vector<int> a(n);
    for(int i=0;i<n-1;i++){
        int l=u[i],r=v[i];
        if(l>r)swap(l,r);
        a[l]++;
        if(r+1<n)a[r+1]--;
    }
    for(int i=1;i<n;i++)a[i]+=a[i-1];
    s.build(a);
}

void change_edge(int x, int y, int z) {
    int l=x,r=y;
    if(l>r)swap(l,r); 
    s.update(min(x,y),max(x,y),-1);
    s.update(min(x,z),max(x,z),1);
}

int lonelytown_query() {
    auto [x,y]=s.query(0,n-1);
    return x==0?y:0;
}

int simulate_query(int e) {
    return 0;
}
