#include<bits/stdc++.h>

using namespace std;

mt19937 rng(time(0));

struct treap{
    struct node{
        char val;
        int prio,sz;
        bool lz;
        node *l,*r;
        node(char val):val(val),prio(rng()),sz(1),lz(false),l(nullptr),r(nullptr){}
    };
    typedef node* nodeptr;
    nodeptr rt=nullptr;
    int sz(nodeptr t){
        return t?t->sz:0;
    }
    void updsz(nodeptr t){
        if(t)t->sz=sz(t->l)+sz(t->r)+1;
    }
    void pushlz(nodeptr t){
        if(t&&t->lz){
            t->lz=false;
            swap(t->l,t->r);
            if(t->l)t->l->lz^=true;
            if(t->r)t->r->lz^=true;
        }
    }
    void merge(nodeptr &t,nodeptr tl,nodeptr tr){
        pushlz(tl);
        pushlz(tr);
        if(!tl)return void(t=tr);
        if(!tr)return void(t=tl);
        if(tl->prio>tr->prio)merge(tl->r,tl->r,tr),t=tl;
        else merge(tr->l,tl,tr->l),t=tr;
        updsz(t);
    }
    void split(nodeptr t,nodeptr &tl,nodeptr &tr,int val){
        pushlz(t);
        if(!t)return void(tl=tr=nullptr);
        if(sz(t->l)+1<=val)split(t->r,t->r,tr,val-sz(t->l)-1),tl=t;
        else split(t->l,tl,t->l,val),tr=t;
        updsz(t);
    }
    void insert(string s,int x){
        nodeptr t1,t2;
        split(rt,t1,t2,x);
        for(auto c:s)merge(t1,t1,new node(c));
        merge(rt,t1,t2);
    }
    void flip(int l,int r){
        nodeptr t1,t2,t3;
        split(rt,t1,t2,l-1);
        split(t2,t2,t3,r-l+1);
        t2->lz^=true;
        merge(rt,t1,t2);
        merge(rt,rt,t3);
    }
    string print(){
        string s="";
        function<void(nodeptr)> dfs=[&](nodeptr t){
            if(!t)return;
            pushlz(t);
            dfs(t->l);
            s.push_back(t->val);
            dfs(t->r);
        };
        dfs(rt);
        return s;
    }
}t;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    t.insert(s,0);
    int q;
    cin >> q;
    while(q--){
        char o;
        cin >> o;
        if(o=='R'){
            int l,r;
            cin >> l >> r;
            t.flip(l,r);
        }else{
            int x;
            string k;
            cin >> x >> k;
            t.insert(k,x);
        }
    }
    cout << t.print();
}