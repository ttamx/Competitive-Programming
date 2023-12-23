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
        int s=a.size()+b.size()-1,n=1<<(32-__builtin_clz(s));
        mint inv=mint(n).inv();
        vm in1(a),in2(b),out(n);
        in1.resize(n),in2.resize(n);
        ntt(in1),ntt(in2);
        for(int i=0;i<n;i++)out[-i&(n-1)]=in1[i]*in2[i]*inv;
        ntt(out);
        return vm(out.begin(),out.begin()+s);
    }
}

#define T mint
using poly = vector<T>;
poly rsz(const poly &p,int n){
    if(n<=sz(p))return poly(begin(p),begin(p)+n);
    poly q=p;q.resize(n);return q;
}
poly shift(poly p,int x) { 
	if (x>=0)p.insert(begin(p),x,0); 
	else assert(sz(p)+x>=0),p.erase(begin(p),begin(p)-x);
	return p; 
}
T eval(const poly &p,T x){
    T res=0;
    for(int i=sz(p)-1;i>=0;i--)res=res*x+p[i];
    return res;
}
poly deriv(const poly &p){
    poly res(max(0,sz(p)-1));
    for(int i=1;i<sz(p);i++)res[i-1]=T(i)*p[i];
    return res;
}
poly integ(const poly &p){
    poly res(sz(p)+1);
    for(int i=0;i<sz(p);i++)res[i+1]=p[i]*invmod(i+1);
    return res;
}
poly &operator+=(poly &lhs,const poly &rhs){
    lhs.resize(max(sz(lhs),sz(rhs)));
    for(int i=0;i<sz(rhs);i++)lhs[i]+=rhs[i];
    return lhs;
}
poly &operator-=(poly &lhs,const poly &rhs){
    lhs.resize(max(sz(lhs),sz(rhs)));
    for(int i=0;i<sz(rhs);i++)lhs[i]-=rhs[i];
    return lhs;
}
poly &operator*=(poly &lhs,const T &rhs){for(auto &x:lhs)x*=rhs;return lhs;}
poly &operator/=(poly &lhs,const T &rhs){for(auto &x:lhs)x/=rhs;return lhs;}
poly operator+(poly lhs,const poly &rhs){return lhs+=rhs;}
poly operator-(poly lhs,const poly &rhs){return lhs-=rhs;}
poly operator*(poly lhs,const T &rhs){return lhs*=rhs;}
poly operator*(const T &lhs,poly rhs){return rhs*=lhs;}
poly operator/(poly lhs,const T &rhs){return lhs/=rhs;}
poly operator*(const poly &lhs,const poly &rhs){return ntt::conv(lhs,rhs);} // change this if can't do ntt
poly &operator*=(poly &lhs,const poly &rhs){return lhs=lhs*rhs;}

poly inv(const poly &p,int n){
    assert(p[0]!=0);
    poly q{p[0].inv()};
    for(int i=2;i/2<n;i*=2)q=2*q-rsz(rsz(p,i)*(q*q),i);
    return rsz(q,n);
}
poly sqrt(const poly &p,int n){
    assert(p[0]==1);
    poly q{1};
    for(int i=2;i/2<n;i*=2)q=invmod(2)*(q+rsz(rsz(p,i)*inv(q,i),i));
    return rsz(q,n);
}
poly log(const poly &p,int n){
    return integ(rsz(deriv(rsz(p,n))*inv(p,n-1),n-1));
}
poly exp(const poly &p,int n){
    poly q{1};
    for(int i=2;i/2<n;i*=2)q=q+rsz(q*(rsz(p,i)-log(q,i)),i);
    return rsz(q,n);
}
poly pow(const poly &p,int n,ll k){
    int l=0;
    while(l<n&&p[l]==0)l++;
    if(db(k*l)>=n)return poly(n,0);
    T a=p[l];
    poly t=a.inv()*shift(p,-l);
    return binpow(a,k)*rsz(shift(exp(k*log(t,n),n),k*l),n);
}
#undef T

const int N=1e5+5;

int n;
string k;
vi s[N];
int a[N],cnt[N];
bool vis[N];
mint fac[N];
vl vk(6);

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i;
    }
    for(int i=1;i<=n;i++)if(!vis[i]){
        int d=0;
        int u=i;
        while(!vis[u]){
            vis[u]=true;
            u=a[u];
            d++;
        }
        cnt[d]++;
    }
    reverse(k.begin(),k.end());
    while(k.size()<102)k.push_back('0');
    reverse(k.begin(),k.end());
    for(int i=0;i<6;i++){
        for(int j=0;j<17;j++)vk[i]=vk[i]*10+k[i*17+j]-'0';
    }
    for(int i=1;i<=n;i++){
        ll res=0,mul=100000000000000000%i;
        for(auto x:vk)res=(res*mul+x)%i;
        int c=gcd(i,res);
        s[i/c].emplace_back(c);
    }
    mint ans=1;
    for(int i=1;i<=n;i++)if(cnt[i]){
        int m=cnt[i];
        vm pw(m+1);
        pw[0]=1;
        for(int j=1;j<=m;j++)pw[j]=pw[j-1]*i;
        poly b(m);
        for(auto j:s[i])if(j<=m)b[j-1]=pw[j-1];
        poly f=exp(integ(b),m+1);
        ans*=f[m]*fac[m];
    }
    cout << ans;
}