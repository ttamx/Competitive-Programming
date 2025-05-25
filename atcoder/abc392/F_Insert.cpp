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

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

struct Treap{
    struct Node{
        int val;
        int prio,sz;
        bool lz;
        Node *l,*r;
        Node(int val):val(val),prio(rng()),sz(1),lz(false),l(nullptr),r(nullptr){}
    };
    typedef Node* Ptr;
    Ptr rt=nullptr;
    int sz(Ptr t){
        return t?t->sz:0;
    }
    void updsz(Ptr t){
        if(t)t->sz=sz(t->l)+sz(t->r)+1;
    }
    void pushlz(Ptr t){
        if(t&&t->lz){
            t->lz=false;
            swap(t->l,t->r);
            if(t->l)t->l->lz^=true;
            if(t->r)t->r->lz^=true;
        }
    }
    void merge(Ptr &t,Ptr tl,Ptr tr){
        pushlz(tl);
        pushlz(tr);
        if(!tl)return void(t=tr);
        if(!tr)return void(t=tl);
        if(tl->prio>tr->prio)merge(tl->r,tl->r,tr),t=tl;
        else merge(tr->l,tl,tr->l),t=tr;
        updsz(t);
    }
    void split(Ptr t,Ptr &tl,Ptr &tr,int val){
        pushlz(t);
        if(!t)return void(tl=tr=nullptr);
        if(sz(t->l)+1<=val)split(t->r,t->r,tr,val-sz(t->l)-1),tl=t;
        else split(t->l,tl,t->l,val),tr=t;
        updsz(t);
    }
    void insert(int x,int val){
        Ptr t1,t2;
        split(rt,t1,t2,x);
        merge(t1,t1,new Node(val));
        merge(rt,t1,t2);
    }
    void flip(int l,int r){
        Ptr t1,t2,t3;
        split(rt,t1,t2,l-1);
        split(t2,t2,t3,r-l+1);
        t2->lz^=true;
        merge(rt,t1,t2);
        merge(rt,rt,t3);
    }
    void query(){
        function<void(Ptr)> dfs=[&](Ptr t){
            if(!t)return;
            pushlz(t);
            dfs(t->l);
            cout << t->val << " ";
            dfs(t->r);
        };
        dfs(rt);
    }
}t;


int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        t.insert(x-1,i+1);
    }
    t.query();
}