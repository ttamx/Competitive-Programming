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

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    k++;
    vector<vi> a(n+2,vi(m+2));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char x;
            cin >> x;
            a[i][j]=x=='#';
        }
    }
    int ans=0;
    auto solve=[&](){
        vector<vi> hor,dia;
        hor=dia=a;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                hor[i][j]+=hor[i][j-1];
                dia[i][j]+=dia[i-1][j-1];
            }
        }
        auto gethor=[&](int i,int j){
            i=max(min(i,n),0);
            j=max(min(j,m),0);
            return hor[i][j];
        };
        auto getdia=[&](int i,int j){
            if(i>n){
                int d=i-n;
                i-=d,j-=d;
            }
            if(j>m){
                int d=j-m;
                i-=d,j-=d;
            }
            if(i<1||j<1)return 0;
            return dia[i][j];
        };
        vector<vi> dp(n+2,vi(m+2));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                dp[i][j]=dp[i-1][j]+gethor(i,j+k-1)-gethor(i,j-1)-getdia(i-1,j+k-1)+getdia(i-k-1,j-1);
                ans=max(ans,dp[i][j]);
            }
        }
    };
    solve();
    reverse(all(a));
    solve();
    for(auto &x:a)reverse(all(x));
    solve();
    reverse(all(a));
    solve();
    cout << ans << "\n";
    auto fac=[&](auto &&self,int i){
        if(i==0)return 1;
        return i*self(self,i-1);
    };
    fac(fac,10);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}