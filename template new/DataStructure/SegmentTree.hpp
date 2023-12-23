#pragma once
#include "../Header.hpp"

template<class Node>
struct segtree{
    int n;
    vector<Node> t;
    segtree(int n=0,Node v=Node()){init(n,v);}
    template<class T>
    segtree(const vector<T> &a){init(a);}
    void init(int n,Node v=Node()){init(vector(n,v));}
    template<class T>
    void init(const vector<T> &a){
        n=sz(a);
        t.assign(4<<31-__builtin_clz(n),Node());
        function<void(int,int,int)> build=[&](int l,int r,int i){
            if(l==r)return void(t[i]=a[l]);
            int m=(l+r)/2;
            build(l,m,i*2);
            build(m+1,r,i*2+1);
            pull(i);
        };
        build(0,n-1,1);
    }
    void pull(int i){
        t[i]=t[i*2]+t[i*2+1];
    }
    void modify(int l,int r,int i,int x,const Node &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
        pull(i);
    }
    void modify(int x,const Node &v){
        modify(0,n-1,1,x,v);
    }
    template<class T>
    void update(int l,int r,int i,int x,const T &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i].apply(l,r,v));
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        pull(i);
    }
    template<class T>
    void update(int x,const T &v){
        update(0,n-1,1,x,v);
    }
    Node query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    Node query(int x,int y){
        return query(0,n-1,1,x,y);
    }
    template<class F>
    int findfirst(int l,int r,int i,int x,int y,const F &f){
        if(y<l||r<x||!f(t[i]))return -1;
        if(l==r)return l;
        int m=(l+r)/2;
        int res=findfirst(l,m,i*2,x,y,f);
        if(res==-1)res=findfirst(m+1,r,i*2+1,x,y,f);
        return res;
    }
    template<class F>
    int findfirst(int x,int y,const F &f){
        return findfirst(0,n-1,1,x,y,f);
    }
    template<class F>
    int findlast(int l,int r,int i,int x,int y,const F &f){
        if(y<l||r<x||!f(t[i]))return -1;
        if(l==r)return l;
        int m=(l+r)/2;
        int res=findlast(m+1,r,i*2+1,x,y,f);
        if(res==-1)res=findlast(l,m,i*2,x,y,f);
        return res;
    }
    template<class F>
    int findlast(int x,int y,const F &f){
        return findlast(0,n-1,1,x,y,f);
    }
};
struct MaxNode{
    ll val;
    MaxNode():val(-LINF){}
    MaxNode(ll x):val(x){}
    void apply(int l,int r,ll x){
        val+=x;
    }
    friend MaxNode operator+(const MaxNode &lhs,const MaxNode &rhs){
        return MaxNode(max(lhs.val,rhs.val));
    }
};
struct MinNode{
    ll val;
    MinNode():val(LINF){}
    MinNode(ll x):val(x){}
    void apply(int l,int r,ll x){
        val+=x;
    }
    friend MinNode operator+(const MinNode &lhs,const MinNode &rhs){
        return MinNode(min(lhs.val,rhs.val));
    }
};
struct SumNode{
    ll val;
    SumNode():val(0){}
    SumNode(ll x):val(x){}
    void apply(int l,int r,ll x){
        val+=x;
    }
    friend SumNode operator+(const SumNode &lhs,const SumNode &rhs){
        return SumNode(lhs.val+rhs.val);
    }
};

