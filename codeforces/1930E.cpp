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

template<uint32_t mod>
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

    constexpr mint &operator++(){return this+=mint(1);}
    constexpr mint &operator--(){return this-=mint(1);}
    constexpr mint operator++(int){
        mint res=*this;
        return this+=mint(1),res;
    }
    constexpr mint operator--(int){
        mint res=*this;
        return this-=mint(1),res;
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
using mint = MontgomeryModInt<MOD>;
using vm = vector<mint>;
mint invmod(int x){
    static vm invs{0,1};
    for(int i=sz(invs);i<=x;i++)
        invs.push_back(-MOD/i*invs[MOD%i]);
    return invs[x];
}

template<class mint>
struct Combinatorics{
    using vm = vector<mint>;
    int n;
    vm fac,invfac;
    Combinatorics(){
        n=0;
        fac=invfac={1};
    }
    Combinatorics(int _n){
        n=0;
        fac=invfac={1};
        init(_n);
    }
    void init(int _n){
        while(n<_n){
            n++;
            fac.emplace_back(fac.back()*n);
            invfac.emplace_back(invfac.back()*invmod(n));
        }
    }
    mint C(int n,int r){
        if(r<0||n<r)return 0;
        init(n);
        return fac[n]*invfac[n-r]*invfac[r];
    }
    mint P(int n,int r){
        if(r<0||n<r)return 0;
        init(n);
        return fac[n]*invfac[n-r];
    }
};
Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    for(int k=1;k<=(n-1)/2;k++){
        mint ans=1;
        for(int t=1;t*k+1<=n;t++){
            ans+=comb.C(n,2*k*t)-comb.C(n-2*k*t+2*k-1,2*k-1);
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}