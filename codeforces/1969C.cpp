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
    vector<int> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    a[0]=a[n+1]=INF;
    k=min(k,n-1);
    vector<vector<ll>> dp(n+2,vector<ll>(k+1,LINF));
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=min(i,k);j++){
            dp[i][j]=dp[i-1][j]+a[i];
            for(int x=1;x<=j;x++){
                dp[i][j]=min(dp[i][j],dp[i-x][j-x]+1LL*min(a[i-x],a[i+1])*x);
            }
        }
    }
    cout << dp[n][k] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}