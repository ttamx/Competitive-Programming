#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n;
    cin >> n;
    vector<string> a(2);
    for(auto &x:a){
        cin >> x;
        x=" "+x;
    }
    vector<array<array<int,2>,2>> dp(n+1);
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++){
        if(a[0][i]=='#'&&a[1][i]=='#'){
            dp[i][0][0]=dp[i-1][0][0];
        }else if(a[0][i]=='#'){
            dp[i][0][0]=dp[i-1][0][1];
            dp[i][0][1]=dp[i-1][0][0];
        }else if(a[1][i]=='#'){
            dp[i][0][0]=dp[i-1][1][0];
            dp[i][1][0]=dp[i-1][0][0];
        }else{
            dp[i][0][0]=min(dp[i-1][0][0]+dp[i-1][1][1],2);
            dp[i][0][1]=dp[i-1][1][0];
            dp[i][1][0]=dp[i-1][0][1];
            dp[i][1][1]=dp[i-1][0][0];
        }
    }
    int ans=dp[n][0][0];
    if(ans==0){
        cout << "None\n";
    }else if(ans==1){
        cout << "Unique\n";
    }else{
        cout << "Multiple\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}