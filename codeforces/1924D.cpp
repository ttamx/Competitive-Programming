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

namespace fft{
    using cd = complex<db>;
    using vc = vector<cd> ;
    void fft(vc &a){
        int n=a.size(),L=31-__builtin_clz(n);
        vc rt(n);
        rt[1]=1;
        for(int k=2;k<n;k*=2){
            cd z=polar(db(1),PI/k);
            for(int i=k;i<2*k;i++)rt[i]=i&1?rt[i/2]*z:rt[i/2];
        }
        vi rev(n);
        for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
        for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
        for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
            cd z=rt[j+k]*a[i+j+k];
            a[i+j+k]=a[i+j]-z;
            a[i+j]+=z;
        }
    }
    #define vt vector<T>
    template<class T>
    vt conv(const vt &a,const vt &b){
        if(a.empty()||b.empty())return {};
        vt res(a.size()+b.size()-1);
        int L=32-__builtin_clz(res.size()),n=1<<L;
        vc in(n),out(n);
        copy(a.begin(),a.end(),in.begin());
        for(int i=0;i<b.size();i++)in[i].imag(b[i]);
        fft(in);
        for(auto &x:in)x*=x;
        for(int i=0;i<n;i++)out[i]=in[-i&(n-1)]-conj(in[i]);
        fft(out);
        for(int i=0;i<res.size();i++)res[i]=out[i].imag()/(4*n);
        return res;
    }
    #undef vt
    template<int M=MOD>
    vl convMod(const vl &a,const vl &b){
        if(a.empty()||b.empty())return {};
        vl res(a.size()+b.size()-1);
        int L=32-__builtin_clz(res.size()),n=1<<L,cut=int(sqrt(M));
        vc in1(n),in2(n),out1(n),out2(n);
        for(int i=0;i<a.size();i++)in1[i]=cd(int(a[i])/cut,int(a[i])%cut); // a1 + i * a2
        for(int i=0;i<b.size();i++)in2[i]=cd(int(b[i])/cut,int(b[i])%cut); // b1 + i * b2
        fft(in1),fft(in2);
        for(int i=0;i<n;i++){
            int j=-i&(n-1);
            out1[j]=(in1[i]+conj(in1[j]))*in2[i]/(2.l*n); // f1 * (g1 + i * g2) = f1 * g1 + i f1 * g2
            out2[j]=(in1[i]-conj(in1[j]))*in2[i]/cd(0.l,2.l*n); // f2 * (g1 + i * g2) = f2 * g1 + i f2 * g2
        }
        fft(out1),fft(out2);
        for(int i=0;i<res.size();i++){
            ll x=round(real(out1[i])),y=round(imag(out1[i]))+round(real(out2[i])),z=round(imag(out2[i]));
            res[i]=((x%M*cut+y)%M*cut+z)%M; // a1 * b1 * cut^2 + (a1 * b2 + a2 * b1) * cut + a2 * b2
        }
        return res;
    }
}

const int N=2005;

mint fac[N],invfac[N];

mint C(int n,int r){
    return fac[n]*invfac[r]*invfac[n-r];
}

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    if(k>min(n,m))return void(cout << "0\n");
    if(n>m)swap(n,m);
    vector<vm> dp(n+2,vm(2));
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=min(i,k);j++){
            mint ways=C(2*j,j)/(j+1);
            dp[i][1]+=dp[i-j][1]*ways;
            dp[i][j==k]+=dp[i-j][0]*ways;
        }
        cerr << dp[i][0] << " ";
        cerr << dp[i][1] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    fac[0]=1;
    for(int i=1;i<N;i++)fac[i]=fac[i-1]*i;
    invfac[0]=1;
    for(int i=1;i<N;i++)invfac[i]=invfac[i-1]*invmod(i);
    int t(1);
    cin >> t;
    while(t--)runcase();
}