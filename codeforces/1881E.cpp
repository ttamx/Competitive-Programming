#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    a.emplace_back(0);
    reverse(a.begin(),a.end());
    vector<int> dp(n+2);
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1]+1;
        if(a[i]<i)dp[i]=min(dp[i],dp[i-a[i]-1]);
    }
    cout << dp[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}