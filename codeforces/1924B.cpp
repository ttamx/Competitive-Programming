#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

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

template<class Node,class Tag>
struct LazySegTree{
    int n;
    vector<Node> t;
    vector<Tag> lz;
    LazySegTree(){}
    LazySegTree(int n,Node v=Node()){init(n,v);}
    template<class T>
    LazySegTree(const vector<T> &a){init(a);}
    void init(int n,Node v=Node()){init(vector<Node>(n,v));}
    template<class T>
    void init(const vector<T> &a){
        n=sz(a);
        t.assign(4<<31-__builtin_clz(n),Node());
        lz.assign(4<<31-__builtin_clz(n),Tag());
        function<void(int,int,int)> build=[&](int l,int r,int i){
            if(l==r)return void(t[i]=a[l]);
            int m=(l+r)/2;
            build(l,m,i*2);
            build(m+1,r,i*2+1);
            pull(i);
        };
        build(0,n-1,1);
    }
    void pull(int i){
        t[i]=t[i*2]+t[i*2+1];
    }
    void apply(int l,int r,int i,const Tag &v){
        t[i].apply(l,r,v);
        lz[i].apply(l,r,v);
    }
    void push(int l,int r,int i){
        int m=(l+r)/2;
        apply(l,m,i*2,lz[i]);
        apply(m+1,r,i*2+1,lz[i]);
        lz[i]=Tag();
    }
    void modify(int l,int r,int i,int x,const Node &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        push(l,r,i);
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
        pull(i);
    }
    void modify(int x,const Node &v){
        modify(0,n-1,1,x,v);
    }
    void update(int l,int r,int i,int x,int y,const Tag &v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,i,v);
        int m=(l+r)/2;
        push(l,r,i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void update(int x,int y,const Tag &v){
        update(0,n-1,1,x,y,v);
    }
    Node query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        push(l,r,i);
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    Node query(int x,int y){
        return query(0,n-1,1,x,y);
    }
    template<class F>
    int findfirst(int l,int r,int i,int x,int y,const F &f){
        if(y<l||r<x||!f(t[i]))return -1;
        if(l==r)return l;
        int m=(l+r)/2;
        push(l,r,i);
        int res=findfirst(l,m,i*2,x,y,f);
        if(res==-1)res=findfirst(m+1,r,i*2+1,x,y,f);
        return res;
    }
    template<class F>
    int findfirst(int x,int y,const F &f){
        return findfirst(0,n-1,1,x,y,f);
    }
    template<class F>
    int findlast(int l,int r,int i,int x,int y,const F &f){
        if(y<l||r<x||!f(t[i]))return -1;
        if(l==r)return l;
        int m=(l+r)/2;
        push(l,r,i);
        int res=findlast(m+1,r,i*2+1,x,y,f);
        if(res==-1)res=findlast(l,m,i*2,x,y,f);
        return res;
    }
    template<class F>
    int findlast(int x,int y,const F &f){
        return findlast(0,n-1,1,x,y,f);
    }
};
struct Tag{
    ll val,nxt;
    bool ok;
    Tag():val(0),nxt(0),ok(false){}
    Tag(ll v,ll d):val(v),nxt(d),ok(true){}
    void apply(int l,int r,const Tag &v){
        if(!v.ok)return;
        ok=true;
        val=v.val;
        nxt=v.nxt;
    }
};
struct Node{
    ll val;
    Node():val(0){}
    Node(ll v):val(v){}
    void apply(int l,int r,const Tag &v){
        if(!v.ok)return;
        ll sz=r-l+1;
        val=v.val*(2*v.nxt-l-r)*sz/2;
    }
    friend Node operator+(const Node &lhs,const Node &rhs){
        return Node(lhs.val+rhs.val);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q;
    cin >> n >> m >> q;
    multiset<pll> h;
    LazySegTree<Node,Tag> s(n);
    vi p(m),v(m);
    for(auto &x:p)cin >> x,x--;
    for(auto &x:v)cin >> x;
    for(int i=0;i<m;i++)h.emplace(p[i],v[i]);
    for(int i=1;i<n-1;i++){
        auto it=h.lower_bound(pii(i,0));
        if(it->first==i)continue;
        s.modify(i,Node(prev(it)->second*(it->first-i)));
    }
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            ll x,v;
            cin >> x >> v;
            x--;
            s.modify(x,Node());
            auto it=h.emplace(x,v);
            auto l=prev(it),r=next(it);
            if(l->first+1<x){
                s.update(l->first+1,x-1,Tag(l->second,x));
            }
            if(x<r->first-1){
                s.update(x+1,r->first-1,Tag(v,r->first));
            }
        }else{
            int l,r;
            cin >> l >> r;
            l--,r--;
            cout << s.query(l,r).val << "\n";
        }
    }
}