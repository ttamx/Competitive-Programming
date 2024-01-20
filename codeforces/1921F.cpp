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
    int n,q;
    cin >> n >> q;
    vl a(n);
    int k=1;
    while(k*k<n)k++;
    for(auto &x:a)cin >> x;
    vector<vl> qs(k+2,vl(n)),qs2(k+2,vl(n));
    for(int i=1;i<=k;i++){
        for(int j=0;j<i;j++){
            qs[i][j]=qs2[i][j]=a[j];
        }
        for(int j=i;j<n;j++){
            qs[i][j]=a[j]+qs[i][j-i];
            qs2[i][j]=a[j]*(j/i+1)+qs2[i][j-i];
        }
    }
    while(q--){
        int l,r,d;
        cin >> l >> d >> r;
        l--;
        r=l+d*(r-1);
        ll ans=0;
        if(d<=k){
            ans=qs2[d][r];
            if(l>=d){
                ans-=qs2[d][l-d];
                ans-=(l/d)*(qs[d][r]-qs[d][l-d]);
            }
        }else{
            int cnt=0;
            for(int i=l;i<=r;i+=d){
                ans+=(++cnt)*a[i];
            }
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}