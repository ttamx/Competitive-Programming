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
    int n;
    cin >> n;
    vi a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<vector<vi>> dp(n+2,vector<vi>(n+2,vi(n+2,INF)));
    dp[0][0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=n;k++){
                dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k]);
                if(i-a[i]<=j){
                    dp[i][i][k]=min(dp[i][i][k],dp[i-1][j][k]+1);
                    dp[i][k][0]=min(dp[i][k][0],dp[i-1][j][k]+2);
                }
                if(j<i+a[i]){
                    dp[i][j][k]=min(dp[i][j][k],dp[i-1][i-1][k]+1);
                }
                auto &x=dp[i][j][min(n,max(k,i+a[i]-1))];
                x=min(x,dp[i-1][j][k]);
            }
        }
        for(int j=n;j>=0;j--){
            for(int k=n;k>=0;k--){
                dp[i][j][k]=min(dp[i][j][k],dp[i][j][k+1]);
                dp[i][j][k]=min(dp[i][j][k],dp[i][j+1][k]);
            }
        }
    }
    int ans=INF;
    for(int i=0;i<=n;i++)ans=min(ans,dp[n][n][i]);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}