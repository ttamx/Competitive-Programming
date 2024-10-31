#include "game.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll gcd2(ll X,ll Y){
    while(Y!=0)tie(X,Y)=make_pair(Y,X%Y);
    return X;
}

int n,m;

struct Treap{
    struct Node;
    using Ptr = Node*;
    struct Node{
        ll val,sum;
        int key,prio;
        Ptr l,r;
        Node(int i,ll v):val(v),sum(v),key(i),prio(rng()),l(),r(){}
    };
    Ptr root;
    Treap():root(){}
    ll get(Ptr t){
        return t?t->sum:0LL;
    }
    void pull(Ptr t){
        if(!t)return;
        t->sum=gcd2(t->val,gcd2(get(t->l),get(t->r)));
    }
    void merge(Ptr &t,Ptr l,Ptr r){
        if(!l)return void(t=r);
        if(!r)return void(t=l);
        if(l->prio>r->prio)merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        pull(t);
    }
    void split(Ptr t,Ptr &l,Ptr &r,int key){
        if(!t)return void(l=r=t);
        if(t->key<=key)split(t->r,t->r,r,key),l=t;
        else split(t->l,l,t->l,key),r=t;
        pull(t);
    }
    void modify(int x,ll v){
        Ptr l,t,r;
        split(root,l,root,x-1);
        split(root,t,r,x);
        if(t)t->val=t->sum=v;
        else t=new Node(x,v);
        merge(root,l,t);
        merge(root,root,r);
    }
    ll query(int x,int y){
        Ptr l,t,r;
        split(root,l,root,x-1);
        split(root,t,r,y);
        ll res=get(t);
        merge(root,l,t);
        merge(root,root,r);
        return res;
    }
};

struct SegTree2D{
    struct Node;
    using Ptr = Node*;
    struct Node{
        Treap tree;
        Ptr l,r;
        Node():tree(),l(),r(){}
    };
    Ptr root;
    SegTree2D():root(){}
    ll get(Ptr t,int x){
        return t?t->tree.query(x,x):0LL;
    }
    void modify(int l,int r,Ptr &t,int x,int y,ll v){
        if(!t)t=new Node();
        if(l<r){
            int m=(l+r)/2;
            if(x<=m)modify(l,m,t->l,x,y,v);
            else modify(m+1,r,t->r,x,y,v);
            v=gcd2(get(t->l,y),get(t->r,y));
        }
        t->tree.modify(y,v);
    }
    void modify(int x,int y,ll v){
        modify(0,n-1,root,x,y,v);
    }
    ll query(int l,int r,Ptr &t,int x,int y,int x2,int y2){
        if(y<l||r<x||!t)return 0LL;
        if(x<=l&&r<=y)return t->tree.query(x2,y2);
        int m=(l+r)/2;
        return gcd2(query(l,m,t->l,x,y,x2,y2),query(m+1,r,t->r,x,y,x2,y2));
    }
    ll query(int x,int y,int x2,int y2){
        return query(0,n-1,root,x,y,x2,y2);
    }
}seg;

void init(int R,int C){
    n=R,m=C;
}

void update(int P,int Q,ll K){
    seg.modify(P,Q,K);
}

ll calculate(int P,int Q,int U,int V){
    return seg.query(P,U,Q,V);
}
