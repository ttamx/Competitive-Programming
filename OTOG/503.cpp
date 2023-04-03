#include<bits/stdc++.h>

using namespace std;

mt19937 rng(time(0));

struct treap{
    struct node{
        int val,prio,sz;
        node *l,*r;
        node(int x):val(x),sz(1),prio(rng()),l(nullptr),r(nullptr){}
    };
    typedef node* pnode;
    pnode rt=nullptr;
    void print(pnode t){
        if(!t)return;
        print(t->l);
        cout << t->val << ' ';
        print(t->r);
    }
    int sz(pnode t){
        return t?t->sz:0;
    }
    void updsz(pnode t){
        if(t)t->sz=sz(t->l)+sz(t->r)+1;
    }
    void merge(pnode &t,pnode l,pnode r){
        if(!l)return void(t=r);
        if(!r)return void(t=l);
        if(l->prio>r->prio)merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        updsz(t);
    }
    void split(pnode t,pnode &l,pnode &r,int key){
        if(!t)return void(l=r=nullptr);
        if(sz(t->l)+1<=key)split(t->r,t->r,r,key-sz(t->l)-1),l=t;
        else split(t->l,l,t->l,key),r=t;
        updsz(t);
    }
    void insert(int x){
        merge(rt,rt,new node(x));
    }
    void rotate(int l,int m,int r){
        pnode t1,t2,t3,t4;
        split(rt,t1,t2,l);
        split(t2,t2,t3,m-l);
        split(t3,t3,t4,r-m);
        merge(rt,t1,t3);
        merge(rt,rt,t2);
        merge(rt,rt,t4);
    }
}t;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        t.insert(x);
    }
    int q;
    cin >> q;
    while(q--){
        int l,r,m;
        cin >> l >> m >> r;
        t.rotate(l,m,r);
    }
    t.print(t.rt);
}