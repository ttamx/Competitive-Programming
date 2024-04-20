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
const ll MOD=456684715444166333;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

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

const mint BASE=11;

const int N=1e6+5;

int n;
string s;
mint pw[N];
mint hsh[3];
mint mem[N],mem2[N];
int ca[N],cb[N];
set<ll> st;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<3;i++)hsh[i]=i*2+1;
    cin >> n >> s;
    for(int i=1;i<n;i++){
        ca[i]=ca[i-1];
        cb[i]=cb[i-1];
        if(s[i]=='A')ca[i]++;
        else cb[i]++;
    }
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*BASE;
    for(int i=1;i<n;i++){
        int chr=2;
        if(ca[i]>cb[i])chr=0;
        if(ca[i]<cb[i])chr=1;
        mem[i]=mem[i-1]+hsh[chr]*pw[i];
    }
    int val=s[0]-'A';
    for(int i=1;i<n;i++){
        int chr=2;
        if(ca[i]+1-val>cb[i]+val)chr=0;
        if(ca[i]+1-val<cb[i]+val)chr=1;
        mem2[i]=mem2[i-1]+hsh[chr]*pw[i];
    }
    for(int i=0;i<n;i++){
        int chr=2;
        if(ca[i]+1-val>cb[i]+val)chr=0;
        if(ca[i]+1-val<cb[i]+val)chr=1;
        st.emplace((mem[i]+hsh[chr]*pw[i+1]+BASE*(mem2[n-1]-mem2[i])).x);
    }
    cout << sz(st);
}