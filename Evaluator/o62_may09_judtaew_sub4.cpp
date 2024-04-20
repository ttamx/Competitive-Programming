#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2505;
const int MOD=1e9+7;

int n,m;
int h[N];
ll dp[2][N][N];
ll ans;

void norm(ll &x){
    if(x>=MOD)x-=MOD;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> h[i];
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++)for(int k=0;k<i;k++)dp[i&1][j][k]=0;
        for(int j=0;j<i;j++)dp[i&1][i-1][j]+=dp[i&1^1][j][0];
        if(i>1&&abs(h[i]-h[i-1])<=m)for(int j=0;j<max(1,i-1);j++)for(int k=0;k<max(1,j);k++){
            dp[i&1][j][k]+=dp[i&1^1][j][k];
            norm(dp[i&1][j][k]);
        }
        for(int j=1;j<i-1;j++)for(int k=0;k<j;k++)if(abs(h[i]-h[j])<=m){
            dp[i&1][i-1][k]+=dp[i&1^1][j][k];
            norm(dp[i&1][i-1][k]);
        }
        for(int j=1;j<i-1;j++)for(int k=1;k<j;k++)if(abs(h[i]-h[k])<=m){
            dp[i&1][i-1][j]+=dp[i&1^1][j][k];
            norm(dp[i&1][i-1][j]);
        }
    }
    for(int j=1;j<n;j++){
        for(int k=1;k<j;k++){
            ans+=dp[n&1][j][k];
            norm(ans);
        }
        ans+=dp[n&1][j][0];
        norm(ans);
    }
    ans*=2;
    norm(ans);
    ans+=dp[n&1][0][0];
    norm(ans);
    ans*=3;
    norm(ans);
    norm(ans);
    cout << ans;
}