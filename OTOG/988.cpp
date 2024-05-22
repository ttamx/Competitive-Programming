#include<bits/stdc++.h>

using namespace std;

const int MOD=5454541;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int ans=n;
    for(int s=2;s<=n;s++){
        vector<vector<int>> dp(s+1,vector<int>(n));
        dp[0][0]=1;
        for(int x:a){
            x%=s;
            auto pdp=dp;
            for(int i=1;i<=s;i++)for(int j=0;j<s;j++){
                dp[i][j]+=pdp[i-1][(j<x?j+s:j)-x];
                if(dp[i][j]>=MOD)dp[i][j]-=MOD;
            }
        }
        ans+=dp[s][0];
        ans%=MOD;
    }
    cout << ans;
}