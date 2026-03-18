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

struct PersistentSegmentTree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        int val;
        Ptr l,r;
        Node(int _val):val(_val),l(nullptr),r(nullptr){}
    };
    void build(int l,int r,Ptr &t){
        t=new Node(0);
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
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
        t->val=t->l->val+t->r->val;
    }
    int query(int l,int r,Ptr tl,Ptr tr,int k){
        if(l==r)return l;
        int m=(l+r)/2;
        int cnt=tr->l->val-tl->l->val;
        if(cnt>=k){
            return query(l,m,tl->l,tr->l,k);
        }else{
            return query(m+1,r,tl->r,tr->r,k-cnt);
        }
    }
};

using Ptr = PersistentSegmentTree::Ptr;

struct Info{
    int mn,mx,sz,pre;
};

struct Stack{
    vector<Info> s;
    vector<Info> dat;
    vector<int> cnt;
    void push(int x){
        Info cur{x,x,1,0};
        int num=0;
        while(!s.empty()&&s.back().mx>=x){
            cur.mx=max(cur.mx,s.back().mx);
            cur.mn=min(cur.mn,s.back().mn);
            cur.sz+=s.back().sz;
            dat.emplace_back(s.back());
            num++;
            s.pop_back();
        }
        cur.pre=cur.sz;
        if(!s.empty()){
            cur.pre+=s.back().pre;
        }
        s.emplace_back(cur);
        cnt.emplace_back(num);
    }
    void pop(){
        assert(!cnt.empty());
        s.pop_back();
        while(cnt.back()--){
            s.emplace_back(dat.back());
            dat.pop_back();
        }
        cnt.pop_back();
    }
    bool empty(){
        return cnt.empty();
    }
    void clear(){
        s.clear();
        dat.clear();
        cnt.clear();
    }
};

struct Queue{
    vector<int> dat;
    Stack l,r;
    void push(int x){
        dat.emplace_back(x);
        r.push(x);
    }
    void pop(){
        if(l.empty()){
            reverse(dat.begin(),dat.end());
            for(auto x:dat){
                l.push(-x);
            }
            dat.clear();
            r.clear();
        }
        l.pop();
    }
    int get(){
        // for(auto e:l.s){
        //     cerr << "(" << e.mn << "," << e.mx << "," << e.sz << "," << e.pre << ") ";
        // }
        // cerr << "\n";
        // for(auto e:r.s){
        //     cerr << "(" << e.mn << "," << e.mx << "," << e.sz << "," << e.pre << ") ";
        // }
        // cerr << "\n";
        // cerr << "\n";
        assert(!(l.empty()&&r.empty()));
        if(l.empty())return r.s[0].sz;
        if(r.empty())return l.s.back().sz;
        int mx=-l.s.back().mn;
        int lo=0,hi=r.s.size();
        while(lo<hi){
            int mid=(lo+hi)/2;
            if(r.s[mid].mn>mx)hi=mid;
            else lo=mid+1;
        }
        if(lo==0)return l.s.back().sz;
        return l.s.back().pre+r.s[lo-1].pre;
    }
};

void runcase(){
    int n,k,q;
    cin >> n >> k >> q;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    PersistentSegmentTree pst;
    vector<Ptr> root(n+1);
    pst.build(1,n,root[0]);
    for(int i=1;i<=n;i++){
        pst.update(1,n,root[i],root[i-1],a[i],+1);
    }
    vector<int> nxt(n+2,n+1);
    Queue ds;
    for(int i=1;i<k;i++){
        ds.push(a[i]);
    }
    for(int i=1;i<=n;i++){
        if(i+k-1<=n){
            ds.push(a[i+k-1]);
        }
        nxt[i]=i+ds.get();
        ds.pop();
    }
    vector<int> dep(n+2),jump(n+2);
    jump[n+1]=n+1;
    for(int i=n;i>=1;i--){
        int j=nxt[i];
        dep[i]=dep[j]+1;
        jump[i]=(dep[j]-dep[jump[j]]==dep[jump[j]]-dep[jump[jump[j]]]?jump[jump[j]]:j);
    }
    while(q--){
        int l,r,k;
        cin >> l >> r >> k;
        int pos=l+k-1;
        while(nxt[l]<=pos){
            l=jump[l]<=pos?jump[l]:nxt[l];
        }
        cout << pst.query(1,n,root[l-1],root[min(nxt[l]-1,r)],pos-l+1) << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}