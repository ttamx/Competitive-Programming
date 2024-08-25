#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    int n=s.size();
    vector<vector<int>> dp(n+1,vector<int>(3,1e9));
    dp[0][0]=dp[0][1]=dp[0][2]=0;
    for(int i=0;i<n;i++){
        if(s[i]=='0'){
            dp[i+1][0]=dp[i][0];
            dp[i+1][1]=min(dp[i][0],dp[i][1]+1);
            dp[i+1][2]=min(dp[i][1],dp[i][2]);
        }else{
            dp[i+1][0]=dp[i][0]+1;
            dp[i+1][1]=min(dp[i][0],dp[i][1]);
            dp[i+1][2]=min(dp[i][1],dp[i][2]+1);
        }
    }
    cout << min({dp[n][0],dp[n][1],dp[n][2]});
}