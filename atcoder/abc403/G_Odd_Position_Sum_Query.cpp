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

struct Info{
    int sz;
    array<ll,2> sum;
	Info(ll v):sz(1),sum{v,0LL}{}
	friend Info operator+(const Info &l,const Info &r){
        Info res=l;
        res.sz+=r.sz;
        int p=l.sz&1;
        res.sum[0]+=r.sum[p];
        res.sum[1]+=r.sum[p^1];
        return res;
    }
};
 
struct Treap{
	struct Node;
	using Ptr = Node*;
    struct Node{
		Info val,sum;
        ll prio,key;
        Ptr l,r;
        Node(Info v,ll k):val(v),sum(v),prio(rng()),key(k),l(),r(){}
    };
    Ptr rt=nullptr;
    void pull(Ptr t){
		if(!t)return;
		t->sum=t->val;
		if(t->l)t->sum=t->l->sum+t->sum;
		if(t->r)t->sum=t->sum+t->r->sum;
    }
    void merge(Ptr &t,Ptr tl,Ptr tr){
        if(!tl)return void(t=tr);
        if(!tr)return void(t=tl);
        if(tl->prio>tr->prio)merge(tl->r,tl->r,tr),t=tl;
        else merge(tr->l,tl,tr->l),t=tr;
        pull(t);
    }
    void split(Ptr t,Ptr &tl,Ptr &tr,ll k){
        if(!t)return void(tl=tr=nullptr);
        if(t->key<=k)split(t->r,t->r,tr,k),tl=t;
        else split(t->l,tl,t->l,k),tr=t;
        pull(t);
    }
    void insert(Info v,ll k){
        Ptr t1,t2;
        split(rt,t1,t2,k);
		merge(t1,t1,new Node(v,k));
        merge(rt,t1,t2);
    }
}t;

const int M=1e9;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    ll z=0;
    while(q--){
        ll x;
        cin >> x;
        x=(x+z)%M+1;
        t.insert(x,x);
        cout << (z=t.rt->sum.sum[0]) << "\n";
    }
}