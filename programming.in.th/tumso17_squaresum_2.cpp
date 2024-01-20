#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
const int MOD=1000000007;
// const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
constexpr T binpow(T a,ll b){T res=1;for(;b>0;b>>=1,a*=a)if(b&1)res*=a;return res;}

struct mint{
    ll x;
    constexpr mint(ll x=0):x(norm(x%MOD)){}
    constexpr ll norm(ll x)const{if(x<0)x+=MOD;if(x>=MOD)x-=MOD;return x;}
    explicit constexpr operator ll()const{return x;}
    constexpr ll mul(ll a,ll b){ll res=(a*b-ll(1.l*a*b/MOD)*MOD)%MOD;if(res<0)res+=MOD;return res;}
    constexpr mint operator-()const{return mint(-x);}
    constexpr mint inv()const{return binpow(mint(*this),MOD-2);}
    constexpr mint &operator+=(const mint &rhs){x=norm(x+rhs.x);return *this;}
    constexpr mint &operator-=(const mint &rhs){x=norm(x-rhs.x);return *this;}
    constexpr mint &operator*=(const mint &rhs){x=mul(x,rhs.x);return *this;}
    constexpr mint &operator/=(const mint &rhs){x=mul(x,rhs.inv().x);return *this;}
    constexpr mint& operator++(){return *this+=1;}
    constexpr mint& operator--(){return *this-=1;}
    constexpr mint operator++(int){mint res=*this;*this+=1;return res;}
    constexpr mint operator--(int){mint res=*this;*this-=1;return res;}
    friend constexpr mint operator+(mint lhs,const mint &rhs){return lhs+=rhs;}
    friend constexpr mint operator-(mint lhs,const mint &rhs){return lhs-=rhs;}
    friend constexpr mint operator*(mint lhs,const mint &rhs){return lhs*=rhs;}
    friend constexpr mint operator/(mint lhs,const mint &rhs){return lhs/=rhs;}
    friend istream &operator>>(istream &is,mint &o){ll x{};is>>x;o=mint(x);return is;}
    friend ostream &operator<<(ostream &os,const mint &o){return os<<o.x;}
    friend constexpr bool operator==(const mint &lhs,const mint &rhs){return lhs.x==rhs.x;};
    friend constexpr bool operator!=(const mint &lhs,const mint &rhs){return lhs.x!=rhs.x;};
};
using vm = vector<mint>;
mint invmod(int x){
    static vm invs{0,1};
    for(int i=sz(invs);i<=x;i++)
        invs.push_back(-MOD/i*invs[MOD%i]);
    return invs[x];
}

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
    mint val;
    Tag():val(0){}
    Tag(ll v):val(v){}
    void apply(int l,int r,const Tag &v){
        val+=v.val;
    }
};
struct Node{
    mint sum,sqsum;
    Node():sum(0),sqsum(0){}
    Node(ll v):sum(v),sqsum(v*v){}
    void apply(int l,int r,const Tag &v){
        int sz=r-l+1;
        sqsum+=2*v.val*sum+v.val*v.val*sz;
        sum+=v.val*sz;
    }
    friend Node operator+(const Node &lhs,const Node &rhs){
        Node res;
        res.sum=lhs.sum+rhs.sum;
        res.sqsum=lhs.sqsum+rhs.sqsum;
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vl a(n);
    for(auto &x:a)cin >> x;
    LazySegTree<Node,Tag> s(a);
    while(q--){
        int t,l,r;
        cin >> t >> l >> r;
        l--,r--;
        if(t==1){
            ll c;
            cin >> c;
            s.update(l,r,Tag(c));
        }else{
            cout << s.query(l,r).sqsum << "\n";
        }
    }
}