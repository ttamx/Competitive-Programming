#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
int a[N];

struct PersistentSegmentTree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        int val;
        Ptr l,r;
        Node(int _val):val(_val),l(nullptr),r(nullptr){}
    };
    Ptr root[N];
    void build(int l,int r,Ptr &t){
        t=new Node(0);
        if(l==r){
            t->val=a[l];
            return;
        }
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
        t->val=max(t->l->val,t->r->val);
    }
    void build(int cur){
        build(1,n,root[cur]);
    }
    void update(int l,int r,Ptr &t,Ptr o,int x,int v){
        t=new Node(*o);
        if(l==r){
            t->val=v;
            return;
        }
        int m=(l+r)/2;
        if(x<=m){
            update(l,m,t->l,o->l,x,v);
        }else{
            update(m+1,r,t->r,o->r,x,v);
        }
        t->val=max(t->l->val,t->r->val);
    }
    void update(int pre,int cur,int x,int v){
        update(1,n,root[cur],root[pre],x,v);
    }
    int query(int l,int r,Ptr t,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t->val;
        int m=(l+r)/2;
        return max(query(l,m,t->l,x,y),query(m+1,r,t->r,x,y));
    }
    int query(int cur,int x,int y){
        return query(1,n,root[cur],x,y);
    }
};

int main(){

}