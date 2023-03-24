#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
ll x=1e12;

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    s=" "+s;
    vector<vector<ll>> dp(n+1,vector<ll>(4,1e18));
    dp[0]={0,0,0,0};
    for(int i=1;i<=n;i++){
        if(s[i]=='0'){
            dp[i][0]=dp[i-1][0];
            dp[i][1]=dp[i-1][1]+x;
            dp[i][2]=dp[i-1][2]+x+1;
        }else{
            dp[i][0]=dp[i-1][0]+x+1;
            dp[i][1]=min(dp[i-1][0],dp[i-1][1]+x+1);
            dp[i][2]=min(dp[i-1][1],dp[i-1][2]);
        }
    }
    cout << min({dp[n][0],dp[n][1],dp[n][2]}) << '\n';
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}