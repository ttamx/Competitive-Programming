#include<bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Treap{
    struct node;
    using pnode = node*;
    struct node{
        int val,freq,sz,prio;
        pnode l,r;
        node(int _val,int _freq=1):val(_val),freq(_freq),sz(_freq),prio(rng()),l(nullptr),r(nullptr){}
    };
    pnode rt;
    Treap():rt(nullptr){}
    static int get_val(pnode t){
        return t?t->val:0;
    }
    static int get_sz(pnode t){
        return t?t->sz:0;
    }
    static void pull(pnode t){
        if(!t)return;
        t->sz=get_sz(t->l)+t->freq+get_sz(t->r);
    }
    static void merge(pnode &t,pnode l,pnode r){
        if(!l)return void(t=r);
        if(!r)return void(t=l);
        if(l->prio>r->prio)merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        pull(t);
    }
    void merge(pnode l,pnode r){
        merge(rt,l,r);
    }
    static void split(pnode t,pnode &l,pnode &r,int k){
        if(!t)return void(l=r=nullptr);
        int x=t->freq+get_sz(t->l);
        if(x>k)split(t->l,l,t->l,k),r=t;
        else split(t->r,t->r,r,k-x),l=t;
        pull(t);
    }
    void split(pnode &l,pnode &r,int k){
        split(rt,l,r,k);
    }
    static void split_first(pnode t,pnode &l,pnode &r){
        if(!t)return void(l=r=nullptr);
        if(t->l)split_first(t->l,l,t->l),r=t;
        else l=t,r=t->r,t->r=nullptr;
        pull(t);
    }
    static void split_by_val(pnode t,pnode &l,pnode &r,int key){
        if(!t)return void(l=r=nullptr);
        if(t->val>=key)split_by_val(t->l,l,t->l,key),r=t;
        else split_by_val(t->r,t->r,r,key),l=t;
        pull(t);
    }
    void split_by_val(pnode &l,pnode &r,int key){
        split_by_val(rt,l,r,key);
    }
    static int get_first(pnode t){
        if(!t)return 0;
        if(t->l)return get_first(t->l);
        return t->val;
    }
    int get_first(){
        return get_first(rt);
    }
    pair<int,int> get(pnode t,int k){
        if(k<=get_sz(t->l))return get(t->l,k);
        if(k>t->freq+get_sz(t->l))return get(t->r,k-t->freq-get_sz(t->l));
        return {t->val,k-get_sz(t->l)};
    }
    pair<int,int> get(int k){
        return get(rt,k);
    }
    void insert(int val,int freq=1){
        merge(rt,new node(val,freq));
    }
    int size(){
        return get_sz(rt);
    }
};
using node = Treap::node;
using pnode = Treap::pnode;

const int N=2e5+5;
const int Q=1e6+5;

int n,q;
int a[N],nxt[N],inv[N],pre[N];
stack<int> s;
Treap t[N],tr;
bool done=false;
vector<tuple<int,int,int>> qr;
int ans[Q];

void insert_main_tree(int id,int freq){
    pnode t1,t2;
    tr.split_by_val(t1,t2,id);
    tr.merge(t1,new node(id,freq));
    tr.merge(tr.rt,t2);
}

void work(){
    if(done)return;
    pnode t1,t2,t3;
    tr.split(t1,t2,n/2);
    int rem=n/2-Treap::get_sz(t1);
    if(!rem)return done=true,tr.merge(t1,t2);
    Treap::split_first(t2,t2,t3);
    int id=inv[t2->val];
    int tar=nxt[id];
    t[id].split(t[id].rt,t2,rem);
    tr.merge(t1,new node(a[id],t[id].size()));
    id=inv[Treap::get_first(t2)];
    tr.merge(tr.rt,t3);
    for(int i=id;t2;i=nxt[i]){
        Treap::split(t2,t[i].rt,t2,nxt[i]-i);
        insert_main_tree(a[i],t[i].size());
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i],inv[a[i]]=i;
    for(int i=1;i<=n;i++){
        while(!s.empty()&&a[i]>a[s.top()]){
            int j=s.top();
            s.pop();
            nxt[j]=i;
        }
        if(s.empty()){
            t[i].insert(a[i]);
            pre[i]=i;
        }else{
            pre[i]=pre[s.top()];
            t[pre[i]].insert(a[i]);
        }
        s.emplace(i);
    }
    inv[0]=n+1;
    while(!s.empty()){
        nxt[s.top()]=n+1;
        s.pop();
    }
    for(int i=1;i<=n;i++)if(pre[i]==i)tr.insert(a[i],t[i].size());
    for(int i=0;i<q;i++){
        int x,y;
        cin >> x >> y;
        qr.emplace_back(x,y,i);
    }
    sort(qr.begin(),qr.end());
    int cnt=0;
    for(auto [x,y,i]:qr){
        while(!done&&cnt<x){
            work();
            cnt++;
        }
        auto [val,rem]=tr.get(y);
        ans[i]=t[inv[val]].get(rem).first;
    }
    for(int i=0;i<q;i++)cout << ans[i] << "\n";
}