#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> p(n+1),w(n+1);
    for(int i=1;i<=n;i++)cin >> p[i] >> w[i];
    vector<vector<int>> dp(n+1,vector<int>(31));
    for(int i=1;i<=n;i++){
        for(int j=0;j<=30;j++){
            dp[i][j]=dp[i-1][j];
            if(j>=w[i])dp[i][j]=max(dp[i][j],dp[i-1][j-w[i]]+p[i]);
        }
    }
    int g;
    cin >> g;
    int ans=0;
    while(g--){
        int m;
        cin >> m;
        ans+=dp[n][m];
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}