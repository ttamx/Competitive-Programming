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

namespace std {

template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

} // namespace std

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

const int N=5005;

mint fac[N],invfac[N];

mint C(int n,int r){
    if(r<0||n<r)return 0;
    return fac[n]*invfac[n-r]*invfac[r];
}

void runcase(){
    int n;
    cin >> n;
    vi a(n),cnt(2*n+2);
    int mn=INF,mx=-INF;
    for(auto &x:a){
        cin >> x;
        cnt[x+n]++;
        mn=min(mn,x+n);
        mx=max(mx,x+n);
    }
    vector<vector<vm>> dp(2,vector<vm>(n+2,vm(4)));
    int cm=cnt[mn];
    dp[mn&1][cm][0]=dp[mn&1][cm][1]=1;
    if(abs(n-mn)==1){
        dp[mn&1][cm][2]=1;
        dp[mn&1][cm][3]=1;
    }
    int e[4]={0,1,1,2};
    int bound=1;
    for(int i=mn+1;i<=mx;i++){
        if(!cnt[i])return void(cout << "0\n");
        for(int j=1;j<=bound;j++)dp[i&1][j]=vm(4);
        for(int j=1;j<=min(bound,cnt[i]+2);j++)for(int k=0;k<4;k++){
            if(cnt[i]-j+e[k]<0)continue;
            mint tmp=C(cnt[i]-1,j-e[k])*dp[i&1^1][j][k];
            bound=max(bound,cnt[i]-j+e[k]);
            dp[i&1][cnt[i]-j+e[k]][k]+=tmp;
            if((k&1)==0){
                dp[i&1][cnt[i]-j+e[k]][k|1]+=tmp;
            }
            if(abs(n-i)==1&&(k&2)==0){
                dp[i&1][cnt[i]-j+e[k]][k|2]+=tmp;
            }
            if(abs(n-i)==1&&k==0){
                dp[i&1][cnt[i]-j+e[k]][3]+=tmp;
            }
        }
    }
    cout << dp[mx&1][1][3] << "\n";
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