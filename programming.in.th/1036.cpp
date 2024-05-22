#include<bits/stdc++.h>

using namespace std;

const int N=10005;
const int K=1<<8;
const int INF=INT_MAX/2;

int n,k;
int a[N],b[N],dp[N][K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        for(int j=0;j<k;j++){
            int x;
            cin >> x;
            b[i]|=x<<j;
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<1<<k;j++){
            dp[i][j]=INF;
        }
    }
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int mask=0;mask<1<<k;mask++){
            dp[i][mask]=dp[i-1][mask];
        }
        for(int mask=0;mask<1<<k;mask++){
            int mask2=mask|b[i];
            dp[i][mask2]=min(dp[i][mask2],dp[i-1][mask]+a[i]);
        }
    }
    cout << dp[n][(1<<k)-1];
}