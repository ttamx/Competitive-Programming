#include "robots.h"
#include<bits/stdc++.h>

using namespace std;

const int K=1<<19;

int n,a,b;
string s;
set<int> ms;

struct segtree{
    int t[K],lz[K];
    void pushlz(int l,int r,int i){
        t[i]+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=0);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void build(){
        build(0,n-1,1);
    }
    void update(int l,int r,int i,int x,int y,int v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,pushlz(l,r,i),void();
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        x=max(x,a);
        y=min(y,n-2);
        update(0,n-1,1,x,y,v);
    }
}seg;

int getleft(int x){
    return *prev(ms.lower_bound(x));
}

int getright(int x){
    return *ms.upper_bound(x);
}

void init_robots(string s, int a, int b){
    ::s=s,::a=a,::b=b;
    n=s.size();
    for(int i=0;i<n;i++)if(s[i]=='R')ms.emplace(i);
    seg.build();
    for(int i=a;i<n-1;i++){
        int res=getright(i)-getleft(i-a+1);
        seg.update(i,i,res);
    }
}

bool update(int k){
    if(s[k]=='R'){
        s[k]='L';
        int l=getleft(k),r=getright(k);
        seg.update(l,k-1,r-k);
        seg.update(k+a,r+a-1,k-l);
        ms.erase(k);
    }else{
        s[k]='R';
        int l=getleft(k),r=getright(k);
        seg.update(l,k-1,k-r);
        seg.update(k+a,r+a-1,l-k);
        ms.emplace(k);
    }
    return seg.t[1]<=b;
}
