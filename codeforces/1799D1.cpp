#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<ll> a(n+1),h(k+1),c(k+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=k;i++)cin >> c[i];
    for(int i=1;i<=k;i++)cin >> h[i];
    vector<ll> dp(k+1,1e18);
    dp[0]=0;
    for(int i=1;i<=n;i++){
        vector<ll> res(k+1,1e18);
        if(a[i]==a[i-1]){
            for(int j=0;j<=k;j++)res[j]=min(res[j],dp[j]+h[a[i]]);
            for(int j=0;j<=k;j++)res[a[i]]=min(res[a[i]],dp[j]+c[a[i]]);
            res[a[i]]=min(res[a[i]],dp[a[i]]+h[a[i]]);
        }else{
            for(int j=0;j<=k;j++)res[j]=min(res[j],dp[j]+c[a[i]]);
            for(int j=0;j<=k;j++)res[a[i-1]]=min(res[a[i-1]],dp[j]+c[a[i]]);
            res[a[i-1]]=min(res[a[i-1]],dp[a[i]]+h[a[i]]);
        }
        dp=res;
    }
    ll ans=1e18;
    for(auto x:dp)ans=min(ans,x);
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}