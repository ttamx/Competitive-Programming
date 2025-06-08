#include "sacredstone.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=1e18;

ll sacredstone(int n,vector<int> a,vector<int> c){
    vector<array<ll,3>> dp(n/2+1,{-INF,-INF,-INF});
    dp[0][0]=0;
    for(int i=0;i<n;i++){
        for(int j=n/2;j>=0;j--){
            dp[j][1]=max(dp[j][1],dp[j][0]+a[i]);
            dp[j][2]=max(dp[j][2],dp[j][0]-a[i]);
            if(j)dp[j][0]=max({dp[j][0],dp[j-1][1]-a[i],dp[j-1][2]+a[i]});
        }
    }
    for(int j=0;j<3;j++){
        vector<ll> d;
        for(int i=1;i<=n/2;i++){
            d.emplace_back(dp[i-1][j]-dp[i][j]);
        }
        assert(is_sorted(d.begin(),d.end()));
    }
    ll ans=0;
    for(int i=0;i*2<=n;i++)ans=max(ans,dp[i][0]+c[n-2*i]);
    for(int i=0;i*2+1<=n;i++)ans=max(ans,dp[i][1]+c[n-2*i-1]);
    return ans;
}