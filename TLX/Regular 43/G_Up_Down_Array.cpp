#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

struct Treap{
    struct Node;
    using Ptr = Node*;
    struct Node{
        ll val;
        array<ll,2> sum;
        int prio,sz;
        Ptr l,r;
        Node(ll val):val(val),sum{val,0LL},prio(rng()),sz(1),l(),r(){}
    };
    Ptr rt=nullptr;
    int sz(Ptr t){
        return t?t->sz:0;
    }
    void pull(Ptr t){
        if(!t)return;
        t->sz=sz(t->l)+sz(t->r)+1;
        t->sum[0]=t->val;
        t->sum[1]=0;
        if(t->l){
            t->sum[0]=t->sum[0]+t->l->sum[1];
            t->sum[1]=t->sum[1]+t->l->sum[0];
        }
        if(t->r){
            t->sum[0]=t->r->sum[0]+t->sum[t->r->sz&1];
            t->sum[1]=t->r->sum[1]+t->sum[(t->r->sz&1)^1];
        }
    }
    void merge(Ptr &t,Ptr tl,Ptr tr){
        if(!tl)return void(t=tr);
        if(!tr)return void(t=tl);
        if(tl->prio>tr->prio)merge(tl->r,tl->r,tr),t=tl;
        else merge(tr->l,tl,tr->l),t=tr;
        pull(t);
    }
    void split(Ptr t,Ptr &tl,Ptr &tr,ll val){
        if(!t)return void(tl=tr=nullptr);
        if(sz(t->l)+1<=val)split(t->r,t->r,tr,val-sz(t->l)-1),tl=t;
        else split(t->l,tl,t->l,val),tr=t;
        pull(t);
    }
    void split_key(Ptr t,Ptr &tl,Ptr &tr,ll val){
        if(!t)return void(tl=tr=nullptr);
        if(t->val<=val)split_key(t->r,t->r,tr,val),tl=t;
        else split_key(t->l,tl,t->l,val),tr=t;
        pull(t);
    }
    void insert(ll x){
        Ptr t1,t2;
        split_key(rt,t1,t2,x);
        merge(t1,t1,new Node(x));
        merge(rt,t1,t2);
    }
    ll query(int l,int r){
        Ptr t1,t2,t3,t4;
        split(rt,rt,t4,r);
        split(rt,rt,t3,r-1);
        split(rt,t1,t2,l);
        ll res=t3->val;
        if(t2)res+=t2->sum[0];
        merge(rt,t1,t2);
        merge(rt,rt,t3);
        merge(rt,rt,t4);
        return res;
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
        int op;
        cin >> op;
        if(op==1){
            int l,r;
            cin >> l >> r;
            cout << t.query(l,r) << "\n";
        }else{
            int x;
            cin >> x;
            t.insert(x);
        }
    }
}