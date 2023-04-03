#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=505;

int n;
ll a[N];
ll dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=-1e18;
    for(int i=1;i+1<=n;i++)dp[i][i+1]=0;
    for(int sz=3;sz<=n;sz++){
        for(int l=1,r=sz;r<=n;l++,r++){
            dp[l][r]=a[l]+a[r]+max(dp[l][r-1],dp[l+1][r]);
            for(int m=l+1;m<r;m++){
                dp[l][r]=max(dp[l][r],dp[l][m]+dp[m][r]+a[l]+a[r]);
            }
        }
    }
    cout << dp[1][n];
}