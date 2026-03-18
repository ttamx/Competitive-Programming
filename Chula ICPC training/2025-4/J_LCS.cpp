#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s,t;
    cin >> s >> t;
    int n=s.size(),m=t.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            dp[i+1][j+1]=max(dp[i+1][j],dp[i][j+1]);
            if(s[i]==t[j]){
                dp[i+1][j+1]=max(dp[i+1][j+1],dp[i][j]+1);
            }
        }
    }
    string ans="";
    for(int i=n,j=m;i>0&&j>0;){
        if(s[i-1]==t[j-1]&&dp[i][j]==dp[i-1][j-1]+1){
            ans.push_back(s[i-1]);
            i--,j--;
        }else if(dp[i][j]==dp[i-1][j]){
            i--;
        }else{
            j--;
        }
    }
    reverse(ans.begin(),ans.end());
    cout << ans << "\n";
}