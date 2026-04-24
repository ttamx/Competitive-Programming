#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define ALL(a) a.begin(),a.end()
#define RALL(a) a.rbegin(),a.rend()
#define SORT(a) sort(ALL(a))
#define RSORT(a) sort(RALL(a))
#define REV(a) reverse(ALL(a))
#define UNI(a) a.erase(unique(ALL(a)),a.end())
#define SZ(a) (int)(a.size())
#define LB(a,x) (int)(lower_bound(ALL(a),x)-a.begin())
#define UB(a,x) (int)(upper_bound(ALL(a),x)-a.begin())
#define MIN(a) *min_element(ALL(a))
#define MAX(a) *max_element(ALL(a))

using ll = long long;
using db = long double;
using i128 = __int128_t;
using u32 = uint32_t;
using u64 = uint64_t;

const int INF=INT_MAX/2;
const ll LINF=LLONG_MAX/4;
const db DINF=numeric_limits<db>::infinity();
const int MOD=998244353;
const int MOD2=1000000007;
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using PQ = priority_queue<T,vector<T>,greater<T>>;
template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

#define vv(T,a,n,...) vector<vector<T>> a(n,vector<T>(__VA_ARGS__))
#define vvv(T,a,n,m,...) vector<vector<vector<T>>> a(n,vector<vector<T>>(m,vector<T>(__VA_ARGS__)))
#define vvvv(T,a,n,m,k,...) vector<vector<vector<vector<T>>>> a(n,vector<vector<vector<T>>>(m,vector<vector<T>>(k,vector<T>(__VA_ARGS__))))

template<class T,class U>
bool chmin(T &a,U b){return b<a?a=b,1:0;}
template<class T,class U>
bool chmax(T &a,U b){return a<b?a=b,1:0;}
template<class T,class U>
T SUM(const U &a){return accumulate(ALL(a),T{});}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());


struct Barrett{
    u32 _m;
    u64 im;

    explicit Barrett(u32 m):_m(m),im((u64)(-1)/m+1){}

    u32 umod()const{return _m;}
    u32 mul(u32 a,u32 b)const{
        u64 z=a;
        z*=b;
        u64 x=(u64)(((unsigned __int128)(z)*im)>>64);
        u64 y=x*_m;
        return (u32)(z-y+(z<y?_m:0));
    }
};

template<int id>
struct DynamicModInt{
    using mint = DynamicModInt;

    u32 x;
    static Barrett bt;

    constexpr DynamicModInt():x(0){}
    constexpr DynamicModInt(ll x):x((x%=get_mod())<0?x+get_mod():x){}
    explicit operator int()const{return (int)x;}
    constexpr static u32 umod(){return bt.umod();}
    constexpr static int get_mod(){return (int)bt.umod();}
    static void set_mod(u32 m){
        assert(m>=1);
        bt=Barrett(m);
    }
    
    mint operator-()const{
        mint res;
        res.val=x?umod()-x:0;
        return res;
    }
    mint operator+()const{return *this;}

    mint inv()const{
        int a=x,b=get_mod(),u=1,v=0,q=0;
        while(b>0){
            q=a/b;
            swap(a-=q*b,b);
            swap(u-=q*v,v);
        }
        return mint(u);
    }
    mint pow(ll n)const{
        mint res=1,a=*this;
        for(;n>0;a*=a,n>>=1)if(n&1)res*=a;
        return res;
    }
    mint &operator+=(const mint &o){
        if((x+=o.x)>=umod())x-=umod();
        return *this;
    }
    mint &operator-=(const mint &o){
        if((x-=o.x)>=umod())x+=umod();
        return *this;
    }
    mint &operator*=(const mint &o){
        x=bt.mul(x,o.x);
        return *this;
    }
    mint &operator/=(const mint &o){
        return *this*=o.inv();
    }

    mint operator+(const mint &o)const{return mint(*this)+=o;}
    mint operator-(const mint &o)const{return mint(*this)-=o;}
    mint operator*(const mint &o)const{return mint(*this)*=o;}
    mint operator/(const mint &o)const{return mint(*this)/=o;}

    mint &operator++(){return *this+=mint(1);}
    mint &operator--(){return *this-=mint(1);}
    mint operator++(int){mint res=*this;*this+=mint(1);return res;}
    mint operator--(int){mint res=*this;*this-=mint(1);return res;}
    
    bool operator==(const mint &o)const{return x==o.x;}
    bool operator!=(const mint &o)const{return x!=o.x;}
    bool operator<(const mint &o)const{return x<o.x;}
    
    friend istream &operator>>(istream &is,mint &o){ll x{};is>>x;o=mint(x);return is;}
    friend ostream &operator<<(ostream &os,const mint &o){return os<<o.x;}
};
template<int id>
Barrett DynamicModInt<id>::bt=Barrett(998244353);

using mint = DynamicModInt<0>;

const int S=305;

using Vec = array<mint,S>;

struct Matrix:array<Vec,S>{
    Matrix(){
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                this->at(i).at(j)=0;
            }
        }
    }
    friend Matrix operator*(const Matrix &l,const Matrix &r){
        Matrix res;
        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){
                for(int k=0;k<S;k++){
                    res[i][j]+=l[i][k]*r[k][j];
                }
            }
        }
        return res;
    }
};

int n,m,mod;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> mod;
    mint::set_mod(mod);
    Matrix a;
    mint x;
    x++;
    ++x;
    for(int i=0;i<m;i++){
        for(int j=i+1;j<m;j++){
            a[i][j]=m-j;
        }
        a[i][i+m]=m-i;
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<=i;j++){
            a[i+m][j]=j*(m-i);
            a[i+m][j+m]=m-i;
        }
        for(int j=i+1;j<m;j++){
            a[i+m][j]=(i+1)*(m-j);
        }
        a[i+m][m<<1]=1;
    }
    a[m<<1][m<<1]=1;
    Vec b{};
    b[0]=1;
    n++;
    while(n>0){
        if(n&1){
            Vec c{};
            for(int i=0;i<S;i++){
                for(int j=0;j<S;j++){
                    c[j]+=b[i]*a[i][j];
                }
            }
            b=move(c);
        }
        a=a*a;
        n>>=1;
    }
    cout << b[2*m] << "\n";
}