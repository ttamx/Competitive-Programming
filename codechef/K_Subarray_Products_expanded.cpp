#line 1 "D:\\cp-library\\template.hpp"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=INT_MAX/2;
const int MOD=998244353;
const int MOD2=1000000007;
const ll LINF=LLONG_MAX/2;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));
#line 2 "D:\\cp-library\\modular-arithmetic\\modint.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-03-17
 * Description: modular arithmetic operations
 */

template<int M,int root=0>
struct ModInt{
    using mint = ModInt;
    int x;
    constexpr ModInt():x(0){}
    constexpr ModInt(ll x):x(norm(x%get_mod())){}
    static int Mod;
    static constexpr int get_mod(){return M>0?M:Mod;}
    static constexpr void set_mod(int Mod_){Mod=Mod_;}
    static constexpr mint get_root(){return mint(root);}
    constexpr int norm(int x)const{if(x<0)x+=get_mod();if(x>=get_mod())x-=get_mod();return x;}
    explicit constexpr operator int()const{return x;}
    constexpr mint operator-()const{return mint()-mint(*this);};
    constexpr mint operator+()const{return mint(*this);};
    constexpr mint inv()const{
        int a=x,b=get_mod(),u=1,v=0,q=0;
        while(b>0){
            q=a/b;
            a-=q*b;
            u-=q*v;
            swap(a,b);
            swap(u,v);
        }
        return mint(u);
    }
    constexpr int mul(int a,int b)const{return 1LL*a*b%get_mod();}
    constexpr mint &operator+=(const mint &rhs){x=norm(x+rhs.x);return *this;}
    constexpr mint &operator-=(const mint &rhs){x=norm(x-rhs.x);return *this;}
    constexpr mint &operator*=(const mint &rhs){x=mul(x,rhs.x);return *this;}
    constexpr mint &operator/=(const mint &rhs){x=mul(x,rhs.inv().x);return *this;}
    constexpr mint &operator++(){return *this+=1;}
    constexpr mint &operator--(){return *this-=1;}
    constexpr mint operator++(int){mint res=*this;*this+=1;return res;}
    constexpr mint operator--(int){mint res=*this;*this-=1;return res;}
    friend constexpr mint operator+(mint lhs,const mint &rhs){return lhs+=rhs;}
    friend constexpr mint operator-(mint lhs,const mint &rhs){return lhs-=rhs;}
    friend constexpr mint operator*(mint lhs,const mint &rhs){return lhs*=rhs;}
    friend constexpr mint operator/(mint lhs,const mint &rhs){return lhs/=rhs;}
    friend istream &operator>>(istream &is,mint &o){ll x{};is>>x;o=mint(x);return is;}
    friend ostream &operator<<(ostream &os,const mint &o){return os<<o.x;}
    friend constexpr bool operator==(const mint &lhs,const mint &rhs){return lhs.x==rhs.x;}
    friend constexpr bool operator!=(const mint &lhs,const mint &rhs){return lhs.x!=rhs.x;}
    friend constexpr bool operator<(const mint &lhs,const mint &rhs){return lhs.x<rhs.x;} // for std::map
};
using mint32 = ModInt<0>;
template<>
int mint32::Mod=int(1e9)+7;

#line 2 "D:\\cp-library\\group\\monoid\\add.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Add Monoid class.
 */

template<class T>
struct AddMonoid{
    using value_type = T;
    static constexpr T op(const T &x,const T &y){return x+y;}
    static constexpr T inverse(const T &x){return -x;}
    static constexpr T unit(){return T(0);}
};

#line 2 "D:\\cp-library\\data-structure\\segment-tree\\lazy-segment-tree.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-01-15
 * Description: Segment Tree with Lazy Propagation
 */

template<class MonoidAction>
struct LazySegmentTree{
    using InfoMonoid = typename MonoidAction::InfoMonoid;
    using TagMonoid = typename MonoidAction::TagMonoid;
    using Info = typename MonoidAction::Info;
    using Tag = typename MonoidAction::Tag;
    int n;
    vector<Info> t;
    vector<Tag> lz;
    LazySegmentTree(){}
    LazySegmentTree(int n,Info v=InfoMonoid::unit()){init(n,v);}
    template<class T>
    LazySegmentTree(const vector<T> &a){init(a);}
    void init(int n,Info v=InfoMonoid::unit()){init(vector<Info>(n,v));}
    template<class T>
    void init(const vector<T> &a){
        n=(int)a.size();
        int m=4<<(31-__builtin_clz(n));
        t.assign(m,InfoMonoid::unit());
        lz.assign(m,TagMonoid::unit());
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
        t[i]=InfoMonoid::op(t[i*2],t[i*2+1]);
    }
    void apply(int i,const Tag &v){
        t[i]=MonoidAction::op(t[i],v);
        lz[i]=TagMonoid::op(lz[i],v);
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=TagMonoid::unit();
    }
    void modify(int l,int r,int i,int x,const Info &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        push(i);
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
        pull(i);
    }
    void modify(int x,const Info &v){
        modify(0,n-1,1,x,v);
    }
    void update(int l,int r,int i,int x,int y,const Tag &v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        int m=(l+r)/2;
        push(i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    void update(int x,int y,const Tag &v){
        update(0,n-1,1,x,y,v);
    }
    Info query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return InfoMonoid::unit();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        push(i);
        return InfoMonoid::op(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    Info query(int x,int y){
        return query(0,n-1,1,x,y);
    }
    template<class F>
    int findfirst(int l,int r,int i,int x,int y,const F &f){
        if(y<l||r<x||!f(t[i]))return -1;
        if(l==r)return l;
        int m=(l+r)/2;
        push(i);
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
        push(i);
        int res=findlast(m+1,r,i*2+1,x,y,f);
        if(res==-1)res=findlast(l,m,i*2,x,y,f);
        return res;
    }
    template<class F>
    int findlast(int x,int y,const F &f){
        return findlast(0,n-1,1,x,y,f);
    }
};

#line 5 "K_Subarray_Products.cpp"

using mint = mint32;

struct Monoid{
    using value_type = mint;
    static constexpr mint op(const mint &a,const mint &b){return a*b;}
    static constexpr mint unit(){return 1;}
};

struct Action{
    using InfoMonoid = AddMonoid<mint>;
    using TagMonoid = Monoid;
    using Info = typename InfoMonoid::value_type;
    using Tag = typename TagMonoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        return a*b;
    }
};


void runcase(){
    int n,k,mod;
    cin >> n >> k >> mod;
    mint::set_mod(mod);
    vector<mint> a(n);
    for(auto &x:a)cin >> x;
    LazySegmentTree<Action> seg(n,mint(0));
    mint ans=0;
    for(int i=0;i<n;i++){
        mint mul=1;
        seg.modify(i,1);
        seg.update(0,i,a[i]);
        ans+=seg.query(max(0,i-k+1),i);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}
