#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<long long> a(n);
    for(auto &x:a)cin >> x;
    vector<pair<long long,long long>> dp(n);
    dp[1]={a[0]+a[1],-a[0]-a[1]};
    for(int i=2;i<n;i++){
        dp[i].first=max(dp[i-1].first,dp[i-1].second)+a[i];
        dp[i].second=max(dp[i-1].first-2*a[i-1],dp[i-1].second+2*a[i-1])-a[i];
    }
    cout << max(dp[n-1].first,dp[n-1].second) << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}