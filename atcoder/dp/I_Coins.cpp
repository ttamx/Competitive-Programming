#include<bits/stdc++.h>

using namespace std;

typedef double db;

const int N=3005;

int n;
db p[N],dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> p[i];
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            dp[i][j]=dp[i-1][j]*(1-p[i]);
            if(j>0)dp[i][j]+=dp[i-1][j-1]*p[i];
        }
    }
    db ans=0;
    for(int i=(n+1)/2;i<=n;i++)ans+=dp[n][i];
    cout << setprecision(10) << ans;
}