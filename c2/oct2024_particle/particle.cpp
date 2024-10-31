#include "particle.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const int K=1<<21;

int n;

struct Segtree{
    struct Tag{
        ll mul,add;
        Tag():mul(1LL),add(0LL){}
        Tag(ll _mul,ll _add):mul(_mul),add(_add){}
        friend Tag operator+(const Tag &lhs,const Tag &rhs){
            return Tag(lhs.mul*rhs.mul,lhs.add*rhs.mul+rhs.add);
        }
    }lz[K];
    ll t[K];
    void apply(int l,int r,int i,const Tag &v){
        t[i]=t[i]*v.mul+v.add*(r-l+1);
        lz[i]=lz[i]+v;
    }
    void push(int l,int m,int r,int i){
        apply(l,m,i*2,lz[i]);
        apply(m+1,r,i*2+1,lz[i]);
        lz[i]=Tag();
    }
    void update(int l,int r,int i,int x,int y,const Tag &v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,i,v);
        int m=(l+r)/2;
        push(l,m,r,i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,const Tag &v){
        update(0,n-1,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0LL;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        push(l,m,r,i);
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    ll query(int x,int y){
        return query(0,n-1,1,x,y);
    }
    int bsearch(int l,int r,int i,ll lhs,ll rhs){
        if(l==r)return l;
        int m=(l+r)/2;
        push(l,m,r,i);
        ll vl=lhs+t[i*2];
        ll vr=rhs+t[i*2+1];
        if(vl>vr){
            return bsearch(l,m,i*2,lhs,t[i*2+1]+rhs);
        }else{
            return bsearch(m+1,r,i*2+1,lhs+t[i*2],rhs);
        }
    }
    int bsearch(ll lhs,ll rhs){
        return bsearch(0,n-1,1,lhs,rhs);
    }
    int findlast(int l,int r,int i,int x,int y){
        if(y<l||r<x||t[i]==0)return -1;
        if(l==r)return l;
        int m=(l+r)/2;
        push(l,m,r,i);
        int res=findlast(m+1,r,i*2+1,x,y);
        if(res==-1)res=findlast(l,m,i*2,x,y);
        return res;
    }
    int findlast(int x,int y){
        return findlast(0,n-1,1,x,y);
    }
}seg;

void init(int _n){
    n=_n;
}

void generateParticle(int l,int r,int p){
    seg.update(l,r,Segtree::Tag(-1,p));
}

ll countSize(int l,int r){
    return seg.query(l,r);
}

int bestPartition(int l,int r){
    ll lsum=seg.query(0,l-1);
    ll rsum=seg.query(r+1,n-1);
    int opt=seg.bsearch(-lsum,-rsum);
    if(opt<=l)return l;
    opt=min(opt,r);
    auto calc=[&](int p){
        return 1.L*seg.query(l,p)*seg.query(p+1,r);
    };
    if(calc(opt-1)>=calc(opt)){
        opt=seg.findlast(0,opt-1);
    }
    return max(opt,l);
}