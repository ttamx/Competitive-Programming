#pragma once
#include "../Header.hpp"

template<class Node>
struct dynamicSegtree{
    struct node;
    using pnode = node*;
    struct node{
        Node val;
        pnode l,r;
        node(Node x=Node()):val(x),l(nullptr),r(nullptr){}
    };
    ll n;
    pnode rt;
    dynamicSegtree(ll n=0){init(n);}
    void init(ll _n){
        n=_n,rt=nullptr;
    }
    Node val(pnode t){
        return t?t->val:Node();
    }
    void pull(pnode &t){
        t->val=val(t->l)+val(t->r);
    }
    void modify(ll l,ll r,pnode &t,ll x,const Node &v){
        if(x<l||r<x)return;
        if(!t)t=new Node();
        if(l==r)return void(t->val);
        ll m=(l+r)/2;
        modify(l,m,t->l,x,v);
        modify(m+1,r,t->r,x,v);
        pull(t);
    }
    void modify(ll x,const Node &v){
        modify(0,n-1,1,x,v);
    }
    template<class T>
    void update(ll l,ll r,pnode &t,ll x,const T &v){
        if(x<l||r<x)return;
        if(!t)t=new Node();
        if(l==r)return void(t->val.apply(l,r,v));
        ll m=(l+r)/2;
        update(l,m,t->l,x,v);
        update(m+1,r,t->r,x,v);
        pull(i);
    }
    template<class T>
    void update(ll x,const T &v){
        update(0,n-1,1,x,v);
    }
    Node query(ll l,ll r,pnode t,ll x,ll y){
        if(y<l||r<x||!t)return Node();
        if(x<=l&&r<=y)return t->val;
        ll m=(l+r)/2;
        return query(l,m,t->l,x,y)+query(m+1,t->r,i*2+1,x,y);
    }
    Node query(ll x,ll y){
        return query(0,n-1,1,x,y);
    }
    template<class F>
    ll findfirst(ll l,ll r,pnode t,ll x,ll y,const F &f){
        if(y<l||r<x||!t||!f(t->val))return -1;
        if(l==r)return l;
        ll m=(l+r)/2;
        ll res=findfirst(l,m,t->l,x,y,f);
        if(res==-1)res=findfirst(m+1,r,t->r,x,y,f);
        return res;
    }
    template<class F>
    ll findfirst(ll x,ll y,const F &f){
        return findfirst(0,n-1,1,x,y,f);
    }
    template<class F>
    ll findlast(ll l,ll r,pnode t,ll x,ll y,const F &f){
        if(y<l||r<x||!t||!f(t->val))return -1;
        if(l==r)return l;
        ll m=(l+r)/2;
        ll res=findlast(m+1,r,t->r,x,y,f);
        if(res==-1)res=findlast(l,m,t->l,x,y,f);
        return res;
    }
    template<class F>
    ll findlast(ll x,ll y,const F &f){
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

