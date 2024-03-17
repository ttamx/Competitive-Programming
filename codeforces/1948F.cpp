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
 
template<class T>
constexpr T binpow(T a,ll b){T res=1;for(;b>0;b>>=1,a*=a)if(b&1)res*=a;return res;}

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

template<class T=mint>
T invmod(int x){
    static vector<T> invs{0,1};
    for(int i=sz(invs);i<=x;i++)invs.push_back(-MOD/i*invs[MOD%i]);
    return invs[x];
}

template<class T=mint>
T fac(int x){
    static vector<T> facs{1};
    for(int i=sz(facs);i<=x;i++)facs.push_back(facs[i-1]*T(i));
    return facs[x];
}

template<class T=mint>
T invfac(int x){
    static vector<T> invs{1};
    for(int i=sz(invs);i<=x;i++)invs.push_back(invs[i-1]*invmod<T>(i));
    return invs[x];
}

template<class T=mint>
T nPr(int n,int r){
    if(r<0||n<r)return T(0);
    return fac<T>(n)*invfac<T>(n-r);
}

template<class T=mint>
T nCr(int n,int r){
    if(r<0||n<r)return T(0);
    return fac<T>(n)*invfac<T>(n-r)*invfac<T>(r);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vi a(n+2),b(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    for(int i=2;i<=n;i++)a[i]+=a[i-1];
    for(int i=2;i<=n;i++)b[i]+=b[i-1];
    int tot=b[n];
    vm ans(tot+2);
    for(int i=tot;i>=0;i--)ans[i]=ans[i+1]+nCr(tot,i);
    mint div=binpow(mint(2),tot).inv();
    while(q--){
        int l,r;
        cin >> l >> r;
        int ua=a[r]-a[l-1];
        int ub=b[r]-b[l-1];
        int va=a[n]-ua;
        int vb=b[n]-ub;
        int req=va+vb-ua+1;
        if(req<0)cout << 1 << " ";
        else if(req>tot)cout << 0 << " ";
        else cout << ans[req]*div << " ";
    }
}