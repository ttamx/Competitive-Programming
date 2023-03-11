#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n,k;
ll h[N],dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> h[i];
    for(int i=2;i<=n;i++)dp[i]=1e18;
    for(int i=2;i<=n;i++)for(int j=1;j<=k&&i-j>=1;j++)dp[i]=min(dp[i],dp[i-j]+llabs(h[i]-h[i-j]));
    cout << dp[n];
}