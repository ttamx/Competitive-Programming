#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n;
ll h[N],dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> h[i];
    h[0]=h[1];
    for(int i=2;i<=n;i++)dp[i]=min(dp[i-1]+llabs(h[i]-h[i-1]),dp[i-2]+llabs(h[i]-h[i-2]));
    cout << dp[n];
}