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

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<pair<ll,ll>> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    sort(a.begin(),a.end(),[&](pair<ll,ll> x,pair<ll,ll> y){
        return y.first*x.second+y.second>x.first*y.second+x.second;
    });
    vector<ll> dp(k+1,1);
    for(auto [x,y]:a){
        auto ndp=dp;
        for(int i=1;i<=k;i++){
            ndp[i]=max(ndp[i],dp[i-1]*x+y);
        }
        swap(dp,ndp);
    }
    cout << dp[k] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}