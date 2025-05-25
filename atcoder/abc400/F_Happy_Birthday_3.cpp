#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=805;
const ll INF=1e18;

int n;
int a[N],c[N];
ll dp[N][N],dp2[N][N];
ll ans=INF;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> c[i];
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)c[i+n]=c[i];
    for(int s=1;s<=n;s++){
        for(int l=1,r=s;r<=2*n;l++,r++){
            dp[l][r]=INF;
            for(int m=l;m<r;m++)dp[l][r]=min(dp[l][r],dp[l][m]+dp[m+1][r]);
            if(c[l]==c[r]){
                int col=c[l];
                dp2[l][r]=dp[l+1][r-1];
                for(int m=l+1;m<r;m++)if(c[m]==col)dp2[l][r]=min(dp2[l][r],dp2[l][m]+dp2[m][r]);
                dp[l][r]=min(dp[l][r],dp2[l][r]+a[col]+s);
            }
            if(s==n)ans=min(ans,dp[l][r]);
        }
    }
    cout << ans;
}