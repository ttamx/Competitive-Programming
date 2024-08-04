#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<int>> dp(n,vector<int>(n));
    for(int i=0;i<n;i++)dp[i][i]=a[i];
    for(int d=1;d<n;d++){
        for(int l=0,r=d;r<n;l++,r++){
            for(int m=l;m<r;m++){
                dp[l][r]=max(dp[l][r],(dp[l][m]+dp[m+1][r])/2);
            }
        }
    }
    cout << dp[0][n-1];
}