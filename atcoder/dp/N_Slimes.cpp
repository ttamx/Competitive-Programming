#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=405;

int n;
ll a[N],qs[N],dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)qs[i]=a[i]+qs[i-1];
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=1e18;
    for(int i=1;i<=n;i++)dp[i][i]=0;
    for(int sz=2;sz<=n;sz++){
        for(int l=1,r=sz;r<=n;l++,r++){
            for(int m=l;m<r;m++){
                dp[l][r]=min(dp[l][r],qs[r]-qs[l-1]+dp[l][m]+dp[m+1][r]);
            }
        }
    }
    cout << dp[1][n];
}