#include<bits/stdc++.h>

using namespace std;

const int N=3005;

int n,k,ans=2e9;
int a[N];
pair<int,int> dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;++i)cin >> a[i];
    for(int i=0;i<=n;++i)dp[i]={2e9,2e9};
    for(int i=2;i<=k;++i)for(int j=1;j<i;++j)dp[i]=min(dp[i],{a[i]+a[j],j});
    for(int i=k+1;i<=n;++i)for(int j=1;j<k;++j)dp[i]=min(dp[i],{a[i]+dp[i-j].first,i-j});
    for(int i=n-k+1;i<=n;++i){
        if(dp[i].second<=n-k+2)for(int j=i+1;j<=n;++j)ans=min(ans,dp[i].first+a[j]);
        else ans=min(ans,dp[i].first);
    }
    cout << ans;
}
