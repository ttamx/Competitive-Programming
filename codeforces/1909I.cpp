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
const int MOD2=1000000007;
const int MOD=998244353;
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

const int N=4005;

int n;
ll x;
mint dp[2][N][N];
mint fac[N],invfac[N];

mint C(int n,int r){
    if(n<0||r<0||n<r)return 0;
    return fac[n]*invfac[n-r]*invfac[r];
}

void gen(int m){
    // cerr << m << ":\n";
    vi a{m/2};
    for(int i=1;i<=n;i++){
        if(m%2){
            if(m/2+i<=n)a.emplace_back(m/2+i);
            if(m/2-i>=1)a.emplace_back(m/2-i);
        }else{
            if(m/2-i>=1)a.emplace_back(m/2-i);
            if(m/2+i<=n)a.emplace_back(m/2+i);
        }
    }
    int k=m%2;
    dp[k][1][0]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<i;j++){
            if(a[i-1]>m/2){
                if(j>=1)dp[k][i][j]+=(j+1)*dp[k][i-1][j-1];
                if(j>=2)dp[k][i][j]+=(i-j)*dp[k][i-1][j-2];
            }else{
                dp[k][i][j]=(i-j)*dp[k][i-1][j];
                if(j+1<n)dp[k][i][j]+=(j+1)*dp[k][i-1][j+1];
            }
            // cerr << dp[k][i][j] << " \n"[j==i-1];
        }
    }
}

namespace ntt{
    const mint g=3;
    void ntt(vm &a){
        int n=a.size(),L=31-__builtin_clz(n);
        vm rt(n);
        rt[1]=1;
        for(int k=2,s=2;k<n;k*=2,s++){
            mint z[]={1,binpow(g,MOD>>s)};
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
    vm conv(const vm &a,const vm &b){
        if(a.empty()||b.empty())return {};
        int s=a.size()+b.size()-1,n=1<<32-__builtin_clz(s);
        mint inv=mint(n).inv();
        vm in1(a),in2(b),out(n);
        in1.resize(n),in2.resize(n);
        ntt(in1),ntt(in2);
        for(int i=0;i<n;i++)out[-i&(n-1)]=in1[i]*in2[i]*inv;
        ntt(out);
        return vm(out.begin(),out.begin()+s);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> x;
    fac[0]=1;
    for(int i=1;i<=n+1;i++)fac[i]=fac[i-1]*i;
    invfac[n+1]=fac[n+1].inv();
    for(int i=n+1;i>=1;i--)invfac[i-1]=invfac[i]*i;
    gen(n),gen(n+1);
    ll ans=0,base=1;
    for(int i=0;i<3*n;i++)base=(base*x)%MOD2;
    for(int m=3;m<=n+1;m++){
        int pre=1;
        for(int i=1;i<=n;i++){
            if(m%2){
                if(m/2+i<=n)pre++;
                else break;
                if(m/2-i>=1)pre++;
                else break;
            }else{
                if(m/2-i>=1)pre++;
                else break;
                if(m/2+i<=n)pre++;
                else break;
            }
        }
        int left=n-pre;
        // cerr << "pre : " << pre << "\n";
        // cerr << m << ":\n";
        // vi a{m/2};
        // for(int i=1;i<=n;i++){
        //     if(m%2){
        //         if(m/2+i<=n)a.emplace_back(m/2+i);
        //         if(m/2-i>=1)a.emplace_back(m/2-i);
        //     }else{
        //         if(m/2-i>=1)a.emplace_back(m/2-i);
        //         if(m/2+i<=n)a.emplace_back(m/2+i);
        //     }
        // }
        // cerr << "a : ";
        // for(auto x:a)cerr << x << " ";
        // cerr << "\n";
        // vector<vm> dp2(n+1,vm(n));
        // dp2[1][0]=1;
        // for(int i=2;i<=n;i++){
        //     for(int j=0;j<i;j++){
        //         if(a[i-1]>m/2){
        //             if(j>=1)dp2[i][j]+=(j+1)*dp2[i-1][j-1];
        //             if(j>=2)dp2[i][j]+=(i-j)*dp2[i-1][j-2];
        //         }else{
        //             dp2[i][j]=(i-j)*dp2[i-1][j];
        //             if(j+1<n)dp2[i][j]+=(j+1)*dp2[i-1][j+1];
        //         }
        //         cerr << dp2[i][j] << " \n"[j==i-1];
        //     }
        // }
        // for(int k=0;k<n;k++){
        //     mint tmp=0;
        //     for(int j=0;j<=k-left;j++){
        //         int x=k-left-j;
        //         tmp+=C(pre-j-1,x)*C(left+j+1,j+x+1)*fac[left]*dp[m%2][pre][j];
        //     }
        //     cerr << tmp << " \n"[k==n-1];
        // }
        vm pa(left+1),pb(pre);
        for(int i=0;i<=left;i++)pa[i]=invfac[i]*invfac[left-i];
        for(int j=0;j<=pre-1;j++)pb[j]=fac[pre-j-1]*fac[left+j+1]*dp[m%2][pre][j];
        vm pc=ntt::conv(pa,pb);
        pc.resize(n-left);
        vm pd(n);
        for(int k=left;k<n;k++)pd[k]=pc[k-left]*fac[left]*invfac[pre-k+left-1]*invfac[k-left+1];
        // for(auto x:pd)cerr << x << " ";
        // cerr << "\n";
        for(int k=0;k<n;k++){
            ans=(ans+(pd[k].x)*base)%MOD2;
            base=(base*x)%MOD2;
        }
    }
    cout << ans;
}