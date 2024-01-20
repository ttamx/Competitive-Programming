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

namespace std {

template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

} // namespace std

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
    ll val;
    Tag():val(0){}
    Tag(ll v):val(v){}
    void apply(int l,int r,const Tag &v){
        val+=v.val;
    }
};
struct Node{
    ll spare,need,cap,ans;
    Node():spare(0),need(0),cap(LINF),ans(0){}
    Node(ll x,ll y,ll z,ll v):spare(x),need(y),cap(z),ans(v){}
    void apply(int l,int r,const Tag &v){

    }
    friend Node operator+(Node lhs,Node rhs){
        Node res;
        res.ans=lhs.ans+rhs.ans;
        ll used=min(lhs.spare,rhs.need);
        lhs.spare-=used;
        rhs.need-=used;
        ll remain=min(rhs.need,lhs.cap);
        res.ans+=rhs.need-remain;
        lhs.cap-=remain;
        res.need=lhs.need+remain;
        ll push=min(lhs.spare,rhs.cap);
        rhs.cap-=push;
        res.spare=push+rhs.spare;
        res.cap=min(lhs.cap,rhs.cap);
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vl a(n),b(n),c(n-1);
    ll tot=0;
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x,tot+=x;
    for(auto &x:c)cin >> x;
    LazySegTree<Node,Tag> s(n);
    auto upd=[&](int i){
        if(i<0||i>=n)return;
        ll d=a[i]-b[i];
        Node res;
        res.spare=max(0ll,d);
        res.need=max(0ll,-d);
        res.cap=i>0?c[i-1]:LINF;
        ll remain=min(res.need,res.cap);
        res.ans=res.need-remain;
        res.need=remain;
        if(i>0)res.cap-=remain;
        s.modify(i,res);
    };
    for(int i=0;i<n;i++)upd(i);
    while(q--){
        int p;
        ll x,y,z;
        cin >> p >> x >> y >> z;
        p--;
        tot+=y-b[p];
        a[p]=x,b[p]=y;
        if(p!=n-1)c[p]=z;
        upd(p);
        upd(p+1);
        auto res=s.query(0,n-1);
        cout << tot-res.need-res.ans << "\n";
    }
}