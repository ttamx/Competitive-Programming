#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

struct ConvexHullTrick{
    struct Line{
        db m,c;
        Line(db _m,db _c):m(_m),c(_c){}
        db eval(db x){
            return m*x+c;
        }
    };
    deque<Line> hull;
    bool bad(const Line &x,const Line &y,const Line &z){
        return (z.c-x.c)*(x.m-y.m)<(y.c-x.c)*(x.m-z.m);
    }
    void insert(db m,db c){
        Line cur(m,c);
        while(hull.size()>=2&&bad(hull.end()[-2],hull.back(),cur)){
            hull.pop_back();
        }
        hull.emplace_back(cur);
    }
    db query(db x){
        assert(!hull.empty());
        while(hull.size()>=2&&hull[0].eval(x)>hull[1].eval(x)){
            hull.pop_front();
        }
        return hull[0].eval(x);
    }
};

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    vector<db> f(n+1),g(n+1),h(n+1);
    for(int i=1;i<=n;i++){
        g[i]=g[i-1]+a[i];
        h[i]=h[i-1]+db(1)/a[i];
        f[i]=f[i-1]+g[i]/a[i];
    }
    auto dp=f;
    for(int t=2;t<=k;t++){
        ConvexHullTrick cht;
        vector<db> ndp(n+1);
        for(int i=t;i<=n;i++){
            cht.insert(-g[i-1],dp[i-1]-f[i-1]+g[i-1]*h[i-1]);
            ndp[i]=cht.query(h[i])+f[i];
        }
        dp=move(ndp);
    }
    cout << dp[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    while(t--)runcase();
}