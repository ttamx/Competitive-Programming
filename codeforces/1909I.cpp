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
// const int MOD=1000000007;
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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    mint x;
    cin >> n >> x;
    for(int m=3;m<=n+1;m++){
        cerr << m << ":\n";
        vector<vm> dp(n+1,vm(n));
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
        cerr << "a : ";
        for(auto x:a)cerr << x << " ";
        cerr << "\n";
        dp[1][0]=1;
        for(int i=2;i<=n;i++){
            for(int j=0;j<i;j++){
                if(a[i-1]>m/2){
                    if(j>=1)dp[i][j]+=(j+1)*dp[i-1][j-1];
                    if(j>=2)dp[i][j]+=(i-j)*dp[i-1][j-2];
                }else{
                    dp[i][j]=(i-j)*dp[i-1][j];
                    if(j+1<n)dp[i][j]+=(j+1)*dp[i-1][j+1];
                }
                cerr << dp[i][j] << " \n"[j==i-1];
            }
        }
    }
}