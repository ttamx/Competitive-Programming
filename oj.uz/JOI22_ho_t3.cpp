#include<bits/stdc++.h>

using namespace std;

const int N=505;

typedef long double ld;

int n,m;
ld a[N],b[N],dp[N][N],dp2[N][N];
vector<pair<ld,ld>> vec;
ld ans=LDBL_MAX;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i] >> b[i];
        if(b[i]<0)b[i]=DBL_MAX;
        vec.emplace_back(b[i],a[i]);
    }
    sort(vec.begin(),vec.end());
    for(int i=1;i<=n;i++)tie(b[i],a[i])=vec[i-1];
    for(int i=1;i<=m;i++)dp2[n+1][i]=DBL_MAX;
    dp2[n+1][0]=0;
    for(int i=n;i>=1;i--){
        for(int j=1;j<=m;j++){
            dp2[i][j]=min(dp2[i+1][j],dp2[i+1][j-1]+a[i]);
        }
        ans=min(ans,dp2[i][m]);
    }
    for(int i=1;i<=m;i++){
        for(int j=0;j<=m;j++)for(int k=0;k<=i;k++)dp[j][k]=LDBL_MAX;
        dp[0][1]=0;
        for(int j=1;j<=m;j++){
            for(int k=1;k<=i;k++){
                dp[j][k]=dp[j-1][k]+a[j]/i;
                if(k>1&&b[j]<=1000)dp[j][k]=min(dp[j][k],dp[j-1][k-1]+b[j]/(k-1));
            }
            ans=min(ans,dp[j][i]+dp2[j+1][m-j]/i);
        }
    }
    cout << fixed << setprecision(12) << ans;
}