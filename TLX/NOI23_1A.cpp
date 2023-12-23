#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
int a[N];
int dp[N];
int cnt[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1]+1;
        if(a[i]<=i){
            cnt[i-a[i]]++;
            dp[i]=min(dp[i],dp[i-a[i]]+a[i]-cnt[i-a[i]]);
        }
    }
    cout << dp[n];
}