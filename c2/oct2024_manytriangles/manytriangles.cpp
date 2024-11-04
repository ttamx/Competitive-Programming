#include "manytriangles.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

ll mincost_color(int c,vector<int> xs,vector<int> ys){
    int n=3*c;
    int b=1<<n;
    vector<ll> dp(b,INF);
    auto area=[&](int i,int j,int k){
        ll x1=xs[i]-xs[j];
        ll y1=ys[i]-ys[j];
        ll x2=xs[i]-xs[k];
        ll y2=ys[i]-ys[k];
        return abs(x1*y2-x2*y1);
    };
    dp[0]=0;
    for(int mask=0;mask<b;mask++){
        if(__builtin_popcount(mask)%3!=0)continue;
        for(int i=0;i<n;i++){
            if(mask>>i&1)continue;
            for(int j=i+1;j<n;j++){
                if(mask>>j&1)continue;
                for(int k=j+1;k<n;k++){
                    if(mask>>k&1)continue;
                    int mask2=mask|(1<<i)|(1<<j)|(1<<k);
                    dp[mask2]=min(dp[mask2],dp[mask]+area(i,j,k));
                }
            }
            break;
        }
    }
    return dp[b-1];
}