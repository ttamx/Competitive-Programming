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
const int MOD=1000000007;
// const int MOD=998244353;
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

int mob[100]={0, 1,-1,-1, 0,-1, 1,-1, 0, 0, 1,-1, 0,-1, 1, 1, 0,-1, 0,-1, 0
, 1, 1,-1, 0, 0, 1, 0, 0,-1,-1,-1, 0, 1, 1, 1, 0,-1, 1, 1, 0
,-1,-1,-1, 0, 0, 1,-1, 0, 0, 0, 1, 0,-1, 0, 1, 0, 1, 1,-1, 0
,-1, 1, 0, 0, 1,-1,-1, 0, 1,-1,-1, 0,-1, 1, 0, 0, 1,-1,-1, 0
, 0, 1,-1, 0, 1, 1, 1, 0,-1, 0, 1, 0, 1, 1, 1, 0,-1, 0, 0};

void runcase(){
    int n,k;
    cin >> n >> k;
    vi a;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x%k==0)a.push_back(x);
    }
    if(a.empty())return void(cout << "0\n");
    for(int i=2;i<k;i++)if(k%i==0)return void(cout << "0\n");
    vm pw(n+1);
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2;
    vector<int> cnt(k);
    for(auto x:a)for(int i=2;i<=k;i++)if(x%i==0)cnt[i]++;
    vm dp(k+1);
    for(int i=2;i<=k;i++){
        dp[i]=pw[cnt[i]]-1;
        cerr << dp[i] << " ";
        for(int j=2;j<i;j++)dp[i]+=dp[j]*mob[j];
        cerr << dp[i] << "\n";
    }
    cout << dp[k] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}