#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=305;
const ll INF=LLONG_MAX/2;

int n,m;
int a[N][2];
ll dp[N][N][N],dp2[N][N][N],dp3[N][N][N];

void chmax(ll &x,ll v){
    x=max(x,v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> a[i][0] >> a[i][1];
    for(int i=0;i<=n+1;i++)for(int j=0;j<=n+1;j++)for(int k=0;k<=n+1;k++)
        dp[i][j][k]=dp2[i][j][k]=dp3[i][j][k]=-INF;
    dp[n+1][0][0]=0;
    for(int i=n;i>=1;i--){
        chmax(dp[i][0][0],dp[i+1][0][0]);
        for(int j=1;j<=n;j++)chmax(dp[i][j-1][0],dp[i+1][j][0]+a[i][0]);
        for(int j=1;j<=n;j++)chmax(dp[i][0][j-1],dp[i+1][0][j]+a[i][1]);
        for(int j=0;j<=n;j++)for(int k=0;k<=n;k++){
            chmax(dp[i][j][k],dp[i+1][j+1][k+1]+a[i][0]+a[i][1]);
            chmax(dp[i][j+1][k],dp[i+1][j][k]-a[i][0]+a[i][1]);
            chmax(dp[i][j][k+1],dp[i+1][j][k]+a[i][0]-a[i][1]);
        }
    }
    if(!m)cout << dp[1][0][0],exit(0);
    dp2[0][0][0]=dp3[0][0][0]=0;
    dp2[0][1][0]=a[1][0];
    dp3[0][0][1]=a[1][1];
    for(int i=1;i<=n;i++){
        chmax(dp2[i][0][0],dp2[i-1][0][0]);
        for(int j=0;j<=n;j++)chmax(dp2[i][j+1][0],dp2[i-1][j][0]+a[i+1][0]);
        for(int j=0;j<=n;j++)chmax(dp2[i][0][j+1],dp2[i-1][0][j]+a[i][1]);
        for(int j=0;j<=n;j++)for(int k=0;k<=n;k++){
            chmax(dp2[i][j+1][k+1],dp2[i-1][j][k]+a[i+1][0]+a[i][1]);
            chmax(dp2[i][j][k],dp2[i-1][j+1][k]-a[i+1][0]+a[i][1]);
            chmax(dp2[i][j][k],dp2[i-1][j][k+1]+a[i+1][0]-a[i][1]);
        }
        chmax(dp3[i][0][0],dp3[i-1][0][0]);
        for(int j=0;j<=n;j++)chmax(dp3[i][j+1][0],dp3[i-1][j][0]+a[i][0]);
        for(int j=0;j<=n;j++)chmax(dp3[i][0][j+1],dp3[i-1][0][j]+a[i+1][1]);
        for(int j=0;j<=n;j++)for(int k=0;k<=n;k++){
            chmax(dp3[i][j+1][k+1],dp3[i-1][j][k]+a[i][0]+a[i+1][1]);
            chmax(dp3[i][j][k],dp3[i-1][j+1][k]-a[i][0]+a[i+1][1]);
            chmax(dp3[i][j][k],dp3[i-1][j][k+1]+a[i][0]-a[i+1][1]);
        }
    }
    ll ans=-INF;
    for(int i=2;i<=n;i++)for(int j=0;j<=n;j++)for(int k=0;k<=n;k++){
        chmax(ans,dp[i+1][j][k]+dp2[i-2][j][k]+a[i][0]-a[i][1]+a[i-1][1]);
        chmax(ans,dp[i+1][j][k]+dp3[i-2][j][k]-a[i][0]+a[i][1]+a[i-1][0]);
    }
    cout << ans;
}