#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    s.push_back(' ');
    reverse(s.begin(),s.end());
    vector<vector<vector<ll>>> dp(n+1,vector<vector<ll>>(5,vector<ll>(2,-2e9)));
    vector<ll> pw(5);
    pw[0]=1;
    for(int i=1;i<5;i++)pw[i]=pw[i-1]*10;
    for(int i=0;i<5;i++)for(int j=0;j<2;j++)dp[0][i][j]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<5;j++){
            if(j<=s[i]-'A'){
                dp[i][s[i]-'A'][0]=max(dp[i][s[i]-'A'][0],dp[i-1][j][0]+pw[s[i]-'A']);
                dp[i][s[i]-'A'][1]=max(dp[i][s[i]-'A'][1],dp[i-1][j][1]+pw[s[i]-'A']);
            }else{
                dp[i][j][0]=max(dp[i][j][0],dp[i-1][j][0]-pw[s[i]-'A']);
                dp[i][j][1]=max(dp[i][j][1],dp[i-1][j][1]-pw[s[i]-'A']);
            }
        }
        for(int j=0;j<5;j++){
            for(int k=0;k<5;k++){
                if(j<=k){
                    dp[i][k][1]=max(dp[i][k][1],dp[i-1][j][0]+pw[k]);
                }else{
                    dp[i][j][1]=max(dp[i][j][1],dp[i-1][j][0]-pw[k]);
                }
            }
        }
    }
    ll ans=-1e18;
    for(int i=0;i<5;i++)for(int j=0;j<2;j++)ans=max(ans,dp[n][i][j]);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}