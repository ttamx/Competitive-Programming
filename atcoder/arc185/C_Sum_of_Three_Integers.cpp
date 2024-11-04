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
using mint = MontgomeryModInt<MOD>;
using vm = vector<mint>;

const mint g=3;

vm rt;
vi rev;

void init(int n){
    int L=31-__builtin_clz(n);
    rt.assign(n,mint(0));
    rev.assign(n,0);
	rt[1]=1;
	for(int k=2,s=2;k<n;k*=2,s++){
		mint z[]={1,binpow(g,MOD>>s)};
		for(int i=k;i<2*k;i++)rt[i]=rt[i/2]*z[i&1];
	}
	for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
}

void ntt(vm &a){
	int n=a.size(),L=31-__builtin_clz(n);
	for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
		mint z=rt[j+k]*a[i+j+k];
		a[i+j+k]=a[i+j]-z;
		a[i+j]+=z;
	}
}

void intt(vm &a){
	int n=a.size(),L=31-__builtin_clz(n);
	for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
		mint z=rt[j+k]*a[i+j+k];
		a[i+j+k]=a[i+j]-z;
		a[i+j]+=z;
	}
}

vm conv(const vm &a,const vm &b){
    if(a.empty()||b.empty())return {};
    int s=a.size()+b.size()-1,n=1<<(32-__builtin_clz(s));
    mint inv=mint(n).inv();
    vm in1(a),in2(b),out(n);
    in1.resize(n),in2.resize(n);
    ntt(in1),ntt(in2);
    for(int i=0;i<n;i++)out[-i&(n-1)]=in1[i]*in2[i]*inv;
    ntt(out);
    return vm(out.begin(),out.begin()+s);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    int kk=1;
    while(kk<=k){
        kk*=2;
    }
    init(kk);
    mint inv=mint(kk).inv();
    vector<pair<int,int>> a;
    vector<int> cnt(k+1);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(cnt[x]<3){
            cnt[x]++;
            a.emplace_back(x,i+1);
        }
    }
    auto check=[&](int l,int r){
        vector<mint> f(kk),g(kk);
        for(int i=l;i<=r;i++){
            int x=a[i].first;
            f[x]++;
            if(x*2<=k){
                g[x*2]++;
            }
        }
        ntt(f);
        ntt(g);
        for(int i=0;i<kk;i++){
            g[i]*=f[i];
        }
        for(int i=0;i<kk;i++){
            f[i]*=f[i]*f[i];
        }
        reverse(f.begin(),f.end());
        reverse(g.begin(),g.end());
        ntt(f);
        ntt(g);
        for(auto &x:f)x*=inv;
        for(auto &x:g)x*=inv;
        for(int i=l;i<=r;i++){
            int x=a[i].first;
            if(x*3<=k){
                g[x*3]--;
                f[x*3]--;
            }
        }
        return f[k]!=3*g[k];
    };
    int l=2,r=a.size();
    while(l<r){
        int m=(l+r)/2;
        if(check(0,m))r=m;
        else l=m+1;
    }
    if(l==a.size()){
        cout << -1;
        exit(0);
    }
    int ans3=l;
    l=0,r=ans3-2;
    while(l<r){
        int m=(l+r+1)/2;
        if(check(m,ans3))l=m;
        else r=m-1;
    }
    int ans1=l;
    for(int i=ans1+1;i<ans3;i++){
        if(a[ans1].first+a[i].first+a[ans3].first==k){
            cout << a[ans1].second << " " << a[i].second << " " << a[ans3].second << "\n";
            exit(0);
        }
    }
    assert(false);
}