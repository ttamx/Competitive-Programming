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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,l;
    cin >> n >> l;
    vi a(n);
    for(auto &x:a)cin >> x;
    int mx=*max_element(all(a));
    vi dp(mx+1,INF);
    dp[0]=0;
    for(int i=0;i<mx;i++)if(dp[i]<INF){
        for(int j=1;j<=l-j;j++){
            ll x=1LL*j*(l-j);
            if(i+x>mx)break;
            dp[i+x]=min(dp[i+x],dp[i]+1);
        }
    }
    for(auto x:a)cout << (dp[x]<INF?dp[x]:-1) << "\n";
}