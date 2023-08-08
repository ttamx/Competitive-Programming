#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=305;
const ll inf=1e18;

int n,m,k;
int s[N];
int p[N][N];
ll dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin >> p[i][j];
    for(int i=1;i<=m;i++)cin >> s[i];
    for(int i=1;i<=m+1;i++)for(int j=0;j<=k;j++)dp[i][j]=inf;
    for(int i=1;i<=m+1;i++){
        for(int j=0;j<=k;j++){
            for(int l=0;i-l>=1&&l+j<=k;l++){
                dp[i][j+l]=min(dp[i][j+l],dp[i-l-1][j]+p[s[i-l-1]][s[i]]);
            }
        }
    }
    cout << dp[m+1][k];
}