#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

mt19937 rng(time(0));

struct info{
    ll ans;
    ll freq[5];
    info(){
        ans=0;
        for(int i=0;i<5;i++)freq[i]=0;
    }
    info(int x){
        ans=0;
        for(int i=0;i<5;i++)freq[i]=0;
        freq[x]=1;
    }
    friend info operator+(info l,info r){
        l.ans+=r.ans;
        ll sum=0;
        for(int i=0;i<5;i++){
            l.ans+=sum*l.freq[i];
            sum+=r.freq[i];
        }
        for(int i=0;i<5;i++)l.freq[i]+=r.freq[i];
        return l;
    }
    void flip(){
        ll sum=0;
        for(int i=0;i<5;i++)sum+=freq[i];
        sum=sum*(sum-1)/2;
        for(int i=0;i<5;i++)sum-=freq[i]*(freq[i]-1)/2;
        ans=sum-ans;
    }
    void set(int x){
        int sum=0;
        for(int i=0;i<5;i++)sum+=freq[i],freq[i]=0;
        freq[x]=sum;
        ans=0;
    }
};

struct treap{
    struct node{
        info val;
        int num,prio,sz,lz;
        bool flip;
        node *l,*r;
        node(int x):val(info(x)),num(x),prio(rng()),sz(1),lz(-1),flip(false),l(nullptr),r(nullptr){}
    };
    typedef node* pnode;
    pnode rt=nullptr;
    int sz(pnode t){
        return t?t->sz:0;
    }
    info val(pnode t){
        return t?t->val:info();
    }
    void upd(pnode t){
        if(!t)return;
        pushlz(t->l);
        pushlz(t->r);
        flip(t->l);
        flip(t->r);
        t->sz=sz(t->l)+1+sz(t->r);
        t->val=val(t->l)+info(t->num)+val(t->r);
    }
    void pushlz(pnode t){
        if(t&&t->lz!=-1){
            t->val.set(t->lz);
            t->num=t->lz;
            if(t->l)t->l->lz=t->lz;
            if(t->r)t->r->lz=t->lz;
            t->lz=-1;
        }
    }
    void flip(pnode t){
        if(t&&t->flip){
            t->flip=false;
            t->val.flip();
            swap(t->l,t->r);
            if(t->l)t->l->flip^=true;
            if(t->r)t->r->flip^=true;
        }
    }
    void print(pnode t){
        if(!t)return;
        pushlz(t);
        flip(t);
        print(t->l);
        cerr << t->num;
        print(t->r);
    }
    void merge(pnode &t,pnode l,pnode r){
        pushlz(l);
        pushlz(r);
        flip(l);
        flip(r);
        if(!l)return void(t=r);
        if(!r)return void(t=l);
        if(l->prio>r->prio)merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        upd(t);
    }
    void split(pnode t,pnode &l,pnode &r,int key){
        pushlz(t);
        flip(t);
        if(!t)return void(l=r=nullptr);
        if(sz(t->l)+1<=key)split(t->r,t->r,r,key-sz(t->l)-1),l=t;
        else split(t->l,l,t->l,key),r=t;
        upd(t);
    }
    void insert(int x){
        merge(rt,rt,new node(x));
    }
    void set(int l,int r,int x){
        pnode t1,t2,t3;
        split(rt,t1,t2,l-1);
        split(t2,t2,t3,r-l+1);
        pushlz(t2);
        flip(t2);
        t2->lz=x;
        pushlz(t2);
        merge(rt,t1,t2);
        merge(rt,rt,t3);
    }
    void flip(int l,int r){
        pnode t1,t2,t3;
        split(rt,t1,t2,l-1);
        split(t2,t2,t3,r-l+1);
        pushlz(t2);
        flip(t2);
        t2->flip^=true;
        flip(t2);
        merge(rt,t1,t2);
        merge(rt,rt,t3);
    }
    ll query(int l,int r){
        pnode t1,t2,t3;
        split(rt,t1,t2,l-1);
        split(t2,t2,t3,r-l+1);
        pushlz(t2);
        flip(t2);
        ll res=t2->val.ans;
        merge(rt,t1,t2);
        merge(rt,rt,t3);
        return res;
    }
}t;

int n,q;
string s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    cin >> s;
    for(auto x:s)t.insert(x-'0');
    while(q--){
        int o;
        cin >> o;
        if(o==1){
            int l,r,x;
            cin >> l >> r >> x;
            t.set(l,r,x);
        }else if(o==2){
            int l,r;
            cin >> l >> r;
            t.flip(l,r);
        }else{
            int l,r;
            cin >> l >> r;
            cout << t.query(l,r) << '\n';
        }
    }
}