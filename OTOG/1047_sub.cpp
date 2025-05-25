#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=1e18;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<array<ll,2>> dp(k+1,{0,-INF});
    for(auto x:a){
        for(int i=k;i>=1;i--){
            dp[i][1]=max(dp[i-1][0],dp[i][1])+x;
            dp[i][0]=max(dp[i][0],dp[i][1]);
        }
    }
    cout << dp[k][0] << "\n";
}