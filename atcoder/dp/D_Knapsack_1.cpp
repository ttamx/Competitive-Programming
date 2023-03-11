#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=105;
const int M=1e5+5;

int n,m;
int w[N];
ll v[N];
ll dp[N][M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> w[i] >> v[i];
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++)dp[i][j]=dp[i-1][j];
        for(int j=w[i];j<=m;j++)dp[i][j]=max({dp[i][j],dp[i-1][j-w[i]]+v[i],dp[i-1][j-1]});
    }
    cout << dp[n][m];
}