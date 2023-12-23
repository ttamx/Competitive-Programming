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
struct Fenwick2D{
    int n,m;
    vector<vector<T>> t;
    Fenwick2D(int n=0,int m=0){init(n,m);}
    void init(int _n,int _m){
        n=_n,m=_m;
        t.assign(n+1,vector<T>(m+1,T{}));
    }
    void update(int x,int y,const T &v){
        for(int i=x+1;i<=n;i+=i&-i)for(int j=y+1;j<=m;j+=j&-j)t[i][j]^=v;
    }
    T query(int x,int y){
        T res{};
        for(int i=x+1;i>0;i-=i&-i)for(int j=y+1;j>0;j-=j&-j)res^=t[i][j];
        return res;
    }
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,m,q;
    cin >> n >> m >> q;
    Fenwick2D<ll> f(n,m);
    map<tuple<int,int,int,int>,ll> mp;
    while(q--){
        int t,a,b,c,d;
        cin >> t >> a >> b >> c >> d;
        a--,b--,c--,d--;
        auto upd=[&](ll hsh){
            f.update(a,b,hsh);
            f.update(a,d+1,hsh);
            f.update(c+1,b,hsh);
            f.update(c+1,d+1,hsh);
        };
        if(t==1){
            ll hsh=rng();
            mp[{a,b,c,d}]^=hsh;
            upd(hsh);
        }else if(t==2){
            ll& hsh=mp[{a,b,c,d}];
            upd(hsh);
            hsh=0;
        }else{
            cout << (f.query(a,b)==f.query(c,d)?"Yes":"No") << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}