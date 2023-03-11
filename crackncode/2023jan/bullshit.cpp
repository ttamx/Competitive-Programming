#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=105;

int dp[N][K];
int a[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        x--;
        for(int j=0;j<k;j++)dp[i][j]=min(dp[i-1][(j+1)%k],dp[i-1][(j+k-1)%k])+1;
        dp[i][x]--;
    }
    int ans=n;
    for(int i=0;i<k;i++)ans=min(ans,dp[n][i]);
    cout << ans;
}