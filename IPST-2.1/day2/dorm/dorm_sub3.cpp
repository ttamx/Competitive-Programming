#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=305;

ll n;
ll a[N];
ll sum=0;
ll dp[N][N];
ll ans[N];

ll calc(ll val,ll p){
    p++;
    if(p>=val)return val;
    ll num=val/p;
    ll rem=val-num*p;
    return rem*((num+1)*(num+1))+(p-rem)*num*num;
}

void init(int N,vector<vector<int> > Req){
    n=N;
    for(auto v:Req){
        int l=v[0],r=v[1];
        l++,r++;
        a[l]++;
        a[r+1]--;
        sum+=r-l+1;
    }
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
    for(int i=1;i<=n;i++){
        for(int j=0;j<305;j++){
            dp[i][j]=1e18;
            for(int k=0;k<=j;k++){
                dp[i][j]=min(dp[i][j],dp[i-1][j-k]+calc(a[i],k));
            }
        }
    }
}
ll least_crowded(int P){
    return dp[n][P];
}
