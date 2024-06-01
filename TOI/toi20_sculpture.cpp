#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> w(n+2),l(n+2);
    for(int i=1;i<=n;i++)cin >> w[i] >> l[i];
    vector<ll> dp(n+2,INF);
    vector<int> dpl(n+2),dpr(n+2);
    dp[0]=0;
    int mx=0;
    for(int i=1;i<=n;i++){
        for(int j=mx+1;j>=1;j--)if(dp[j-1]<=l[i]){
            dp[j]=min(dp[j],dp[j-1]+w[i]);
            dpl[i]=max(dpl[i],j);
        }
        mx=max(mx,dpl[i]);
    }
    dp.assign(n+2,0);
    dp[0]=INF;
    mx=0;
    for(int i=n;i>=1;i--){
        for(int j=mx+1;j>=1;j--)if(dp[j-1]>=w[i]){
            dp[j]=max(dp[j],min(dp[j-1]-w[i],l[i]));
            mx=max(mx,j);
        }
        dpr[i]=mx;
    }
    int ans=1;
    for(int i=1;i<=n;i++){
        ans=max(ans,dpl[i]+dpr[i+1]);
    }
    cout << ans << "\n";
    for(int i=1;i<=n;i++)if(dpl[i]+dpr[i+1]==ans)cout << i << " ";
}