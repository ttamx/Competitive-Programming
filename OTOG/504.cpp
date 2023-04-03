#include<bits/stdc++.h>

using namespace std;

mt19937 rng(time(0));

struct treap{
    struct node{
        int val,prio,sz;
        bool lz;
        node *l,*r;
        node(int val):val(val),sz(1),prio(rng()),lz(false),l(nullptr),r(nullptr){}
    };
    typedef node* pnode;
    pnode rt=nullptr;
    int sz(pnode t){
        return t?t->sz:0;
    }
    void updsz(pnode t){
        if(t)t->sz=sz(t->l)+sz(t->r)+1;
    }
    void pushlz(pnode t){
        if(t&&t->lz){
            t->lz=false;
            swap(t->l,t->r);
            if(t->l)t->l->lz^=true;
            if(t->r)t->r->lz^=true;
        }
    }
    void merge(pnode &t,pnode l,pnode r){
        pushlz(l);
        pushlz(r);
        if(!l)return void(t=r);
        if(!r)return void(t=l);
        if(l->prio>r->prio)merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        updsz(t);
    }
    void split(pnode t,pnode &l,pnode &r,int key){
        pushlz(t);
        if(!t)return void(l=r=nullptr);
        if(sz(t->l)<key)split(t->r,t->r,r,key-sz(t->l)-1),l=t;
        else split(t->l,l,t->l,key),r=t;
        updsz(t);
    }
    void insert(int x){
        merge(rt,rt,new node(x));
    }
    void flip(int l,int r){
        pnode t1,t2,t3;
        split(rt,t1,t2,l);
        split(t2,t2,t3,r-l);
        if(t2)t2->lz^=true;
        merge(rt,t1,t2);
        merge(rt,rt,t3);
    }
    void print(pnode t){
        pushlz(t);
        if(!t)return;
        print(t->l);
        cout << t->val << ' ';
        print(t->r);
    }
    void print(){
        print(rt);
    }
}t;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        t.insert(x);
    }
    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        t.flip(l,r);
    }
    t.print();
}