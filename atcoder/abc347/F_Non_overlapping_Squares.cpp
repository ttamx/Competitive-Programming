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

const int N=1005;

int n,m;
ll a[N][N],b[N][N],qs[N][N];
ll dp[4][N][N];
ll ans;

void solve(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            qs[i][j]=a[i][j]+qs[i][j-1]+qs[i-1][j]-qs[i-1][j-1];
        }
    }
    for(int i=m;i<=n;i++){
        for(int j=m;j<=n;j++){
            ll val=qs[i][j]-qs[i][j-m]-qs[i-m][j]+qs[i-m][j-m];
            dp[0][i][j]=max({dp[0][i][j-1],dp[0][i-1][j],val});
        }
    }
    for(int i=m;i<=n;i++){
        for(int j=n;j>=m;j--){
            ll val=qs[i][j]-qs[i][j-m]-qs[i-m][j]+qs[i-m][j-m];
            dp[1][i][j]=max({dp[1][i][j+1],dp[1][i-1][j],val});
        }
    }
    for(int i=n;i>=m;i--){
        for(int j=m;j<=n;j++){
            ll val=qs[i][j]-qs[i][j-m]-qs[i-m][j]+qs[i-m][j-m];
            dp[2][i][j]=max({dp[2][i][j-1],dp[2][i+1][j],val});
        }
    }
    for(int i=n;i>=m;i--){
        for(int j=n;j>=m;j--){
            ll val=qs[i][j]-qs[i][j-m]-qs[i-m][j]+qs[i-m][j-m];
            dp[3][i][j]=max({dp[3][i][j+1],dp[3][i+1][j],val});
        }
    }
    for(int i=m;i<=n-m;i++){
        for(int j=m;j<=n-m;j++){
            ans=max(ans,dp[0][i][n]+dp[2][i+m][j]+dp[3][i+m][j+m]);
            ans=max(ans,dp[2][i+m][n]+dp[0][i][j]+dp[1][i][j+m]);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> a[i][j];
            b[i][j]=a[i][j];
        }
    }
    solve();
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=b[j][i];
    solve();
    cout << ans;
}