#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> a(m+1);
    for(int i=1;i<=m;i++){
        cin >> a[i];
        a[i]+=a[i-1];
    }
    vector<int> fac(n+1),dp(m+1);
    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=1LL*fac[i-1]*i%MOD;
    }
    int ans=fac[n];
    for(int i=1;i<=m;i++){
        dp[i]=fac[a[i]];
        for(int j=0;j<i;j++){
            dp[i]=(dp[i]-1LL*fac[a[i]-a[j]]*dp[j]%MOD+MOD)%MOD;
        }
        ans=(ans-1LL*dp[i]*fac[n-a[i]]%MOD+MOD)%MOD;
    }
    cout << ans;
}