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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N=2e5+5;
const int K=1<<19;
const mint BASE=rng();

int n,q;
vi a[3];
string s;
mint pw[N],pre[N];

int get(char c){
    if(c=='J')return 0;
    if(c=='O')return 1;
    if(c=='I')return 2;
    return -1;
}

struct segtree{
    mint t[K];
    int lz[K];
    void push(int l,int r,int i){
        if(lz[i]==-1)return;
        t[i]=lz[i]*(pre[r]-pre[l-1]);
        if(l<r)lz[i*2]=lz[i*2+1]=lz[i];
        lz[i]=-1;
    }
    void build(int l,int r,int i){
        lz[i]=-1;
        if(l==r)return void(t[i]=get(s[l])*pw[l]);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(0,n-1,1);
    }
    void update(int l,int r,int i,int x,int y,int v){
        push(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,push(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,int v){
        update(0,n-1,1,x,y,v);
    }
}st;

vi convert(const string &s){
    vi res;
    for(auto x:s)res.emplace_back(get(x));
    return res;
}

mint hsh(const vi &a){
    mint res=0;
    for(int i=0;i<n;i++)res+=a[i]*pw[i];
    return res;
}

vi cross(const vi &a,const vi &b){
    vi res(n);
    for(int i=0;i<n;i++)res[i]=(a[i]+b[i])*2%3;
    return res;
}

vm val;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    pw[0]=pre[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*BASE,pre[i]=pre[i-1]+pw[i];
    for(int i=0;i<3;i++){
        string x;
        cin >> x;
        a[i]=convert(x);
    }
    for(int i=0;i<3;i++){
        val.emplace_back(hsh(a[i]));
        val.emplace_back(hsh(cross(a[i],a[(i+1)%3])));
        val.emplace_back(hsh(cross(cross(a[i],a[(i+1)%3]),a[(i+2)%3])));
    }
    cin >> q >> s;
    st.build();
    bool ok=false;
    for(auto x:val)ok|=st.t[1]==x;
    cout << (ok?"Yes\n":"No\n");
    while(q--){
        int l,r;
        char c;
        cin >> l >> r >> c;
        l--,r--;
        st.update(l,r,get(c));
        ok=false;
        for(auto x:val)ok|=st.t[1]==x;
        cout << (ok?"Yes\n":"No\n");
    }
}