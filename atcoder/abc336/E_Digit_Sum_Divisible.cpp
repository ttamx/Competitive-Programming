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

string s;

ll solve(ll x){
    int sum=0;
    ll val=0;
    vl pw(15);
    pw[0]=1;
    for(int i=1;i<15;i++)pw[i]=pw[i-1]*10%x;
    vector<vl> dp(x+2,vl(x+2));
    for(int i=0;i<sz(s);i++){
        vector<vl> ndp(x+2,vl(x+2));
        for(int dsum=0;dsum<=x;dsum++){
            for(int d=0;d<10;d++){
                if(dsum+d>x)break;
                for(int mod=0;mod<x;mod++){
                    ndp[dsum+d][(mod+d*pw[sz(s)-i-1])%x]+=dp[dsum][mod];
                }
            }
        }
        for(int d=0;d<s[i]-'0';d++){
            if(sum+d>x)break;
            ndp[sum+d][(val+d*pw[sz(s)-i-1])%x]++;
        }
        sum+=s[i]-'0';
        val+=(s[i]-'0')*pw[sz(s)-i-1];
        val%=x;
        swap(dp,ndp);
    }
    return dp[x][0]+(val==0&&sum==x);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> s;
    ll ans=0;
    for(int i=1;i<=126;i++)ans+=solve(i);
    cout << ans;
}