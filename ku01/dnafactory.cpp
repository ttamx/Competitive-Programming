#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> dp(n+2);
    for(int i=0;i<m;i++){
        int x,y;
        cin >> x >> y;
        dp[x]++;
        dp[y+1]--;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        dp[i]+=dp[i-1];
        ans=max(ans,dp[i]);
    }
    cout << ans;
}