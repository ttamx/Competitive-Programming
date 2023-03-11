#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> dp(722);
    for(int i=0;i<n;i++){
        int a,b;
        cin >> a >> b;
        if(a<b){
            dp[a+1]++,dp[b+1]--;
            dp[a+361]++,dp[b+361]--;
        }else{
            dp[1]++,dp[b]--;
            dp[a+1]++,dp[b+361]--;
            dp[a+361]++,dp[721]--;
        }
    }
    for(int i=1;i<=720;i++)dp[i]+=dp[i-1];
    int ans=0;
    for(int i=1;i<=720;i++){
        if(dp[i])dp[i]=dp[i-1]+1;
        ans=max(ans,dp[i]);
    }
    cout << min(ans,360);
}