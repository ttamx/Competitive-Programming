#line 2 "D:\\cp-library\\content\\template\\Header.hpp"
#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<db, db>;
const int INF = 0x3fffffff;
// const int MOD=1000000007;
const int MOD = 998244353;
const ll LINF = 0x1fffffffffffffff;
const db DINF = numeric_limits<db>::infinity();
const db EPS = 1e-9;
const db PI = acos(db(-1));

#line 3 "D:\\cp-library\\content\\modular-arithmetic\\MontgomeryModInt.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-03-17
 * Description: modular arithmetic operators using Montgomery space
 */

template<uint32_t mod,uint32_t root=0>
struct MontgomeryModInt{
    using mint = MontgomeryModInt;
    using i32 = int32_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    static constexpr u32 get_r(){
        u32 res=1;
        for(i32 i=0;i<5;i++)res*=2-mod*res;
        return res;
    }

    static const u32 r=get_r();
    static const u32 n2=-u64(mod)%mod;
    static_assert(mod<(1<<30));
    static_assert((mod&1)==1);
    static_assert(r*mod==1);

    u32 x;

    constexpr MontgomeryModInt():x(0){}
    constexpr MontgomeryModInt(const int64_t &v):x(reduce(u64(v%mod+mod)*n2)){}

    static constexpr u32 get_mod(){return mod;}
    static constexpr mint get_root(){return mint(root);}
    explicit constexpr operator ll()const{return val();}

    static constexpr u32 reduce(const u64 &v){
        return (v+u64(u32(v)*u32(-r))*mod)>>32;
    }

    constexpr u32 val()const{
        u32 res=reduce(x);
        return res>=mod?res-mod:res;
    }

    constexpr mint inv()const{
        int a=val(),b=mod,u=1,v=0,q;
        while(b>0){
            q=a/b;
            a-=q*b;
            u-=q*v;
            swap(a,b);
            swap(u,v);
        }
        return mint(u);
    }

    constexpr mint &operator+=(const mint &rhs){
        if(i32(x+=rhs.x-2*mod)<0)x+=2*mod;
        return *this;
    }
    constexpr mint &operator-=(const mint &rhs){
        if(i32(x-=rhs.x)<0)x+=2*mod;
        return *this;
    }
    constexpr mint &operator*=(const mint &rhs){
        x=reduce(u64(x)*rhs.x);
        return *this;
    }
    constexpr mint &operator/=(const mint &rhs){
        return *this*=rhs.inv();
    }

    constexpr mint &operator++(){return *this+=mint(1);}
    constexpr mint &operator--(){return *this-=mint(1);}
    constexpr mint operator++(int){
        mint res=*this;
        return *this+=mint(1),res;
    }
    constexpr mint operator--(int){
        mint res=*this;
        return *this-=mint(1),res;
    }

    constexpr mint operator-()const{return mint()-mint(*this);};
    constexpr mint operator+()const{return mint(*this);};

    friend constexpr mint operator+(const mint &lhs,const mint &rhs){return mint(lhs)+=rhs;}
    friend constexpr mint operator-(const mint &lhs,const mint &rhs){return mint(lhs)-=rhs;}
    friend constexpr mint operator*(const mint &lhs,const mint &rhs){return mint(lhs)*=rhs;}
    friend constexpr mint operator/(const mint &lhs,const mint &rhs){return mint(lhs)/=rhs;}
    friend constexpr bool operator==(const mint &lhs,const mint &rhs){
        return (lhs.x>=mod?lhs.x-mod:lhs.x)==(rhs.x>=mod?rhs.x-mod:rhs.x);
    }
    friend constexpr bool operator!=(const mint &lhs,const mint &rhs){
        return (lhs.x>=mod?lhs.x-mod:lhs.x)!=(rhs.x>=mod?rhs.x-mod:rhs.x);
    }
    friend constexpr bool operator<(const mint &lhs,const mint &rhs){
        return (lhs.x>=mod?lhs.x-mod:lhs.x)<(rhs.x>=mod?rhs.x-mod:rhs.x); // for std::map
    }

    friend istream &operator>>(istream &is,mint &o){
        int64_t v;
        is >> v;
        o=mint(v);
        return is;
    }
    friend ostream &operator<<(ostream &os,const mint &o){
        return os << o.val();
    }
};
using mint = MontgomeryModInt<MOD,3>;
using vm = vector<mint>;

#line 3 "D:\\cp-library\\content\\data-structure\\LazySegmentTree.hpp"

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
        n=sz(a);
        t.assign(4<<31-__builtin_clz(n),InfoMonoid::unit());
        lz.assign(4<<31-__builtin_clz(n),TagMonoid::unit());
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

#line 3 "D:\\cp-library\\content\\monoid\\MonoidBase.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-05-16
 * Description: Monoid Base class.
 */

template<class T,T (*combine)(T,T),T (*identity)()>
struct MonoidBase{
    using value_type = T;
    static constexpr T op(const T &x,const T &y){return combine(x,y);}
    static constexpr T unit(){return identity();}
};

#line 3 "D:\\cp-library\\content\\monoid\\MonoidActionBase.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-05-16
 * Description: Monoid Action Base class.
 */

template<class MInfo,class MTag,typename MInfo::value_type
    (*combine)(typename MInfo::value_type,typename MTag::value_type)>
struct MonoidActionBase{
    using InfoMonoid = MInfo;
    using TagMonoid = MTag;
    using Info = typename InfoMonoid::value_type;
    using Tag = typename TagMonoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        return combine(a,b);
    }
};

#line 6 "F_Two_Sequence_Queries.cpp"

struct Info{
    mint suma,sumb,ans,len;
    Info():suma(0),sumb(0),ans(0),len(0){}
    Info(mint _suma,mint _sumb,mint _ans,mint _len):suma(_suma),sumb(_sumb),ans(_ans),len(_len){}
};

Info merge_info(Info a,Info b){
    return Info(a.suma+b.suma,a.sumb+b.sumb,a.ans+b.ans,a.len+b.len);
}

Info unit_info(){
    return Info();
}

struct Tag{
    mint a,b;
    Tag():a(0),b(0){}
    Tag(mint _a,mint _b):a(_a),b(_b){}
};

Tag merge_tag(Tag a,Tag b){
    return Tag(a.a+b.a,a.b+b.b);
}

Tag unit_tag(){
    return Tag();
}

Info apply_tag(Info a,Tag b){
    return Info(a.suma+b.a*a.len,a.sumb+b.b*a.len,a.ans+b.a*a.sumb+b.b*(a.suma+b.a*a.len),a.len);
}

using MInfo = MonoidBase<Info,merge_info,unit_info>;
using MTag = MonoidBase<Tag,merge_tag,unit_tag>;
using Mono = MonoidActionBase<MInfo,MTag,apply_tag>;

void runcase(){
    int n,q;
    cin >> n >> q;
    vm a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    vector<Info> c(n);
    for(int i=0;i<n;i++)c[i]=Info(a[i],b[i],a[i]*b[i],1);
    LazySegmentTree<Mono> s(c);
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int l,r;
            mint v;
            cin >> l >> r >> v;
            l--,r--;
            s.update(l,r,Tag(v,0));
        }else if(t==2){
            int l,r;
            mint v;
            cin >> l >> r >> v;
            l--,r--;
            s.update(l,r,Tag(0,v));
        }else{
            int l,r;
            cin >> l >> r;
            l--,r--;
            cout << s.query(l,r).ans << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
