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

template<class T>
constexpr T binpow(T a,ll b){T res=1;for(;b>0;b>>=1,a*=a)if(b&1)res*=a;return res;}

template<class mint>
struct NTT{
	using vm = vector<mint>;
	
	static constexpr mint root=mint::get_root();

	static void ntt(vm &a){
		int n=a.size(),L=31-__builtin_clz(n);
		vm rt(n);
		rt[1]=1;
		for(int k=2,s=2;k<n;k*=2,s++){
			mint z[]={1,binpow(root,MOD>>s)};
			for(int i=k;i<2*k;i++)rt[i]=rt[i/2]*z[i&1];
		}
		vi rev(n);
		for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
		for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
			mint z=rt[j+k]*a[i+j+k];
			a[i+j+k]=a[i+j]-z;
			a[i+j]+=z;
		}
	}
	static vm conv(const vm &a,const vm &b){
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
	vm operator()(const vm &a,const vm &b){
		return conv(a,b);
	}
};

template<class mint>
struct FormalPowerSeries:vector<mint>{
    using vector<mint>::vector;
    using FPS=FormalPowerSeries;

    FPS &operator+=(const FPS &rhs){
        if(rhs.size()>this->size())this->resize(rhs.size());
        for(int i=0;i<rhs.size();i++)(*this)[i]+=rhs[i];
        return *this;
    }
    FPS &operator+=(const mint &rhs){
        if(this->empty())this->resize(1);
        (*this)[0]+=rhs;
        return *this;
    }
    FPS &operator-=(const FPS &rhs){
        if(rhs.size()>this->size())this->resize(rhs.size());
        for(int i=0;i<rhs.size();i++)(*this)[i]-=rhs[i];
        return *this;
    }
    FPS &operator-=(const mint &rhs){
        if(this->empty())this->resize(1);
        (*this)[0]-=rhs;
        return *this;
    }
    FPS &operator*=(const FPS &rhs){
        auto res=NTT<mint>()(*this,rhs);
        return *this=FPS(res.begin(),res.end());
    }
    FPS &operator*=(const mint &rhs){
        for(auto &a:*this)a*=rhs;
        return *this;
    }
    friend FPS operator+(FPS lhs,const FPS &rhs){return lhs+=rhs;}
    friend FPS operator+(FPS lhs,const mint &rhs){return lhs+=rhs;}
    friend FPS operator+(const mint &lhs,FPS &rhs){return rhs+=lhs;}
    friend FPS operator-(FPS lhs,const FPS &rhs){return lhs-=rhs;}
    friend FPS operator-(FPS lhs,const mint &rhs){return lhs-=rhs;}
    friend FPS operator-(const mint &lhs,FPS rhs){return -(rhs-lhs);}
    friend FPS operator*(FPS lhs,const FPS &rhs){return lhs*=rhs;}
    friend FPS operator*(FPS lhs,const mint &rhs){return lhs*=rhs;}
    friend FPS operator*(const mint &lhs,FPS rhs){return rhs*=lhs;}
    
    FPS operator-(){return (*this)*-1;}

    FPS rev(){
        FPS res(*this);
        reverse(res.beign(),res.end());
        return res;
    }
    FPS pre(int sz){
        FPS res(this->begin(),this->begin()+min((int)this->size(),sz));
        if(res.size()<sz)res.resize(sz);
        return res;
    }
    FPS shrink(){
        FPS res(*this);
        while(!res.empty()&&res.back()==mint{})res.pop_back();
        return res;
    }
    FPS operator>>(int sz){
        if(this->size()<=sz)return {};
        FPS res(*this);
        res.erase(res.begin(),res.begin()+sz);
        return res;
    }
    FPS operator<<(int sz){
        FPS res(*this);
        res.insert(res.begin(),sz,mint{});
        return res;
    }
    FPS diff(){
        const int n=this->size();
        FPS res(max(0,n-1));
        for(int i=1;i<n;i++)res[i-1]=(*this)[i]*mint(i);
        return res;
    }
    FPS integral(){
        const int n=this->size();
        FPS res(n+1);
        res[0]=0;
        if(n>0)res[1]=1;
        auto mod=mint::get_mod();
        for(int i=2;i<=n;i++)res[i]=(-res[mod%i])*(mod/i);
        for(int i=0;i<n;i++)res[i+1]*=(*this)[i];
        return res;
    }
    mint eval(const mint &x){
        mint res=0,w=1;
        for(auto &a:*this)res+=a*w,w*=x;
        return res;
    }

    FPS inv(int deg=-1){
        assert(!this->empty()&&(*this)[0]!=mint(0));
        if(deg==-1)deg=this->size();
        FPS res{mint(1)/(*this)[0]};
        for(int i=2;i>>1<deg;i<<=1){
            res=(res*(mint(2)-res*pre(i))).pre(i);
        }
        return res.pre(deg);
    }
    FPS log(int deg=-1){
        assert(!this->empty()&&(*this)[0]==mint(1));
        if(deg==-1)deg=this->size();
        return (pre(deg).diff()*inv(deg)).pre(deg-1).integral();
    }
    FPS exp(int deg=-1){
        assert(this->empty()||(*this)[0]==mint(0));
        if(deg==-1)deg=this->size();
        FPS res{mint(1)};
        for(int i=2;i>>1<deg;i<<=1){
            res=(res*(pre(i)-res.log(i)+mint(1))).pre(i);
        }
        return res.pre(deg);
    }
    FPS pow(ll k,int deg=-1){
        const int n=this->size();
        if(deg==-1)deg=n;
        if(k==0){
            FPS res(deg);
            if(deg)res[0]=mint(1);
            return res;
        }
        for(int i=0;i<n;i++){
            if(__int128_t(i)*k>=deg)return FPS(deg,mint(0));
            if((*this)[i]==mint(0))continue;
            mint rev=mint(1)/(*this)[i];
            FPS res=(((*this*rev)>>i).log(deg)*k).exp(deg);
            res=((res*binpow((*this)[i],k))<<(i*k)).pre(deg);
            return res;
        }
        return FPS(deg,mint(0));
    }
};
using FPS=FormalPowerSeries<mint>;

const int N=2e6+5;

mint fac[N],invfac[N];

mint C(int n,int r){
    return fac[n]*invfac[n-r]*invfac[r];
}

void runcase(){
    int l,n;
    cin >> l >> n;
    mint ans=C(l,2*n);
    FPS a(l),b(l);
    for(int i=0;i<l;i++)a[i]=C(n+i,i);
    for(int i=0;i*2<l;i++)b[i*2]=C(n+i-1,i);
    FPS res=a*b;
    ans-=res[l-2*n];
    cout << ans*2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    fac[0]=1;
    for(int i=1;i<N;i++)fac[i]=fac[i-1]*i;
    invfac[N-1]=fac[N-1].inv();
    for(int i=N-1;i>=1;i--)invfac[i-1]=invfac[i]*i;
    int t(1);
    cin >> t;
    while(t--)runcase();
}