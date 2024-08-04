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

const int N=2005;

mint fac[N];
mint ifac[N];

mint P(int n,int r){
    if(n<0||r<0||n<r)return 0;
    return fac[n]*ifac[n-r];
}

mint C(int n,int r){
    if(n<0||r<0||n<r)return 0;
    return fac[n]*ifac[r]*ifac[n-r];
}

void runcase(){
    int n,b,k;
    cin >> n >> b >> k;
    vector<vm> dp(n+1,vm(k+1));
    dp[n][k]=1;
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<=k;j++){
            dp[i][j]=dp[i+1][j]*j;
            if(j<k)dp[i][j]+=dp[i+1][j+1]*(b-j);
        }
    }
    auto calc=[&](const vector<int> &a){
        mint ans=0;
        vector<bool> used(b);
        int cnt=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<a[i];j++){
                int res=cnt;
                if(!used[j])res++;
                if(res==k){
                    ans+=binpow(mint(k),n-i-1);
                }else if(res<k){
                    ans+=dp[i+1][res];
                }
            }
            if(!used[a[i]]){
                used[a[i]]=true;
                cnt++;
            }
        }
        if(cnt==k)ans++;
        return ans;
    };
    vector<int> l(n),r(n);
    for(auto &x:l)cin >> x;
    for(auto &x:r)cin >> x;
    mint ans=calc(r);
    if(l!=vector<int>(n,0)){
        for(int i=n-1;i>=0;i--){
            if(l[i]>0){
                l[i]--;
                break;
            }else{
                l[i]=b-1;
            }
        }
        ans-=calc(l);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    fac[0]=1;
    for(int i=1;i<N;i++)fac[i]=fac[i-1]*i;
    ifac[N-1]=fac[N-1].inv();
    for(int i=N-2;i>=0;i--)ifac[i]=ifac[i+1]*(i+1);
    int t(1);
    cin >> t;
    while(t--)runcase();
}