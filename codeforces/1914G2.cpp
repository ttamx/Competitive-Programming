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

struct DSU{
    vi p,sz;
    DSU(int n=0){
        init(n);
    }
    void init(int n){
        p.resize(n);
        iota(all(p),0);
        sz.assign(n,1);
    }
    int fp(int u){
        return p[u]=(u==p[u]?u:fp(p[u]));
    }
    bool same(int u,int v){
        return fp(u)==fp(v);
    }
    bool merge(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return false;
        sz[u]+=sz[v];
        p[v]=u;
        return true;
    }
    int getsz(int u){
        return sz[fp(u)];
    }
};

void runcase(){
    int n;
    cin >> n;
    vi l(n,-1),r(n,-1);
    for(int i=0;i<2*n;i++){
        int x;
        cin >> x;
        x--;
        if(l[x]==-1)l[x]=i;
        else r[x]=i;
    }
    vi a(2*n,-1),b(2*n,-1);
    for(int i=0;i<n;i++)a[l[i]]=i;
    for(int i=0;i<n;i++)b[r[i]]=i;
    mint ans=1;
    vi vec;
    for(int p=0;p<2*n;p++)if(a[p]!=-1){
        int i=a[p];
        vec.emplace_back(i);
        int mx=r[i];
        while(p+1<mx)if(a[++p]!=-1){
            int j=a[p];
            mx=max(mx,r[j]);
        }
    }
    DSU dsu(n);
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    for(int p=0;p<2*n;p++)if(a[p]!=-1){
        int i=a[p];
        while(!pq.empty()&&pq.top().first<l[i])pq.pop();
        while(!pq.empty()&&pq.top().first<r[i]){
            dsu.merge(i,pq.top().second);
            pq.pop();
        }
        pq.emplace(r[i],i);
    }
    priority_queue<pii> pq2;
    for(int p=2*n-1;p>=0;p--)if(b[p]!=-1){
        int i=b[p];
        while(!pq2.empty()&&pq2.top().first>r[i])pq2.pop();
        while(!pq2.empty()&&pq2.top().first>l[i]){
            dsu.merge(i,pq2.top().second);
            pq2.pop();
        }
        pq2.emplace(l[i],i);
    }
    for(auto i:vec)ans*=2*dsu.getsz(i);
    cout << sz(vec) << " " << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}