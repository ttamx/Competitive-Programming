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

const int N=82;

int n;
int p[N][N],r[N][N],d[N][N];
pll dp[N][N][N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin >> p[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<n;j++)cin >> r[i][j];
    for(int i=1;i<n;i++)for(int j=1;j<=n;j++)cin >> d[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int x=1;x<=i;x++)for(int y=1;y<=j;y++)dp[i][j][x][y]=pll(LINF,-LINF);
    dp[1][1][1][1]=pll(0,0);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int x=1;x<=i;x++)for(int y=1;y<=j;y++){
        if(j<n){
            ll rem=-dp[i][j][x][y].second-r[i][j];
            ll need=0;
            if(rem<0)need=(-rem+p[x][y]-1)/p[x][y];
            rem+=need*p[x][y];
            dp[i][j+1][x][y]=min(dp[i][j+1][x][y],pll(dp[i][j][x][y].first+need+1,-rem));
            dp[i][j+1][i][j+1]=min(dp[i][j+1][i][j+1],pll(dp[i][j][x][y].first+need+1,-rem));
        }
        if(i<n){
            ll rem=-dp[i][j][x][y].second-d[i][j];
            ll need=0;
            if(rem<0)need=(-rem+p[x][y]-1)/p[x][y];
            rem+=need*p[x][y];
            dp[i+1][j][x][y]=min(dp[i+1][j][x][y],pll(dp[i][j][x][y].first+need+1,-rem));
            dp[i+1][j][i+1][j]=min(dp[i+1][j][i+1][j],pll(dp[i][j][x][y].first+need+1,-rem));
        }
    }
    ll ans=LINF;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)ans=min(ans,dp[n][n][i][j].first);
    cout << ans << "\n";
}