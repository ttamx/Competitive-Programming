#include<bits/stdc++.h>

using namespace std;

const int N=755;
const int INF=INT_MAX/2;

int n;
int a[N][N];
int dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            cin >> a[j][i];
        }
    }
    for(int l=n;l>=1;l--){
        dp[l][l]=0;
        for(int r=l+1;r<=n;r++){
            dp[l][r]=INF;
            for(int i=l+1;i<=r;i++){
                dp[l][r]=min(dp[l][r],dp[l][i-1]+dp[i][r]+max(a[l][i],0));
            }
        }
        for(int r=l;r<=n;r++){
            for(int i=r+1;i<=n;i++){
                dp[l][r]+=max(-a[l][i],0);
            }
        }
    }
    cout << dp[1][n];
}