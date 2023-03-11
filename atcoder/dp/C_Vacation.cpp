#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n;
ll a[N],b[N],c[N],dp[N][3];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i] >> b[i] >> c[i];
    for(int i=1;i<=n;i++){
        dp[i][0]=max(dp[i-1][1],dp[i-1][2])+a[i];
        dp[i][1]=max(dp[i-1][0],dp[i-1][2])+b[i];
        dp[i][2]=max(dp[i-1][0],dp[i-1][1])+c[i];
    }
    cout << max({dp[n][0],dp[n][1],dp[n][2]});
}