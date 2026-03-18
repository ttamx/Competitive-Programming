#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int n=s.size();
        auto t=s;
        reverse(t.begin(),t.end());
        vector<vector<int>> dp(n+1,vector<int>(n+1,INT_MAX/2));
        dp[0][0]=0;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                if(i+1<=n){
                    dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
                }
                if(j+1<=n){
                    dp[i][j+1]=min(dp[i][j+1],dp[i][j]+1);
                }
                if(i+1<=n&&j+1<=n){
                    dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]+(s[i]!=t[j]));
                }
            }
        }
        cout << dp[n][n]/2 << "\n";
    }
}