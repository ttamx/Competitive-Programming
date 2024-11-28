#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD=998244353;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

ll inv(ll a){
    return binpow(a,MOD-2);
}

signed main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    if(n==1||k==1){
        cout << 1 << "\n";
        exit(0);
    }
    vector<ll> fac(n),ifac(n);
    fac[0]=1;
    for(int i=1;i<n;i++){
        fac[i]=fac[i-1]*i%MOD;
    }
    ifac[n-1]=inv(fac[n-1]);
    cerr << fac[n-1]*ifac[n-1]%MOD;
    for(int i=n-1;i>=1;i--){
        ifac[i-1]=ifac[i]*i%MOD;
    }
    vector<ll> dp(n);
    dp[0]=dp[1]=1;
    for(int i=2;i<n;i++){
        dp[i]=dp[i-1]*2%MOD;
        if(i>=k){
            dp[i]=(dp[i]-dp[i-k]+MOD)%MOD;
        }
    }
    ll ans=1;
    for(int i=1;i<n;i++){
        ans=(ans+dp[i]*2%MOD*fac[n-1]%MOD*ifac[i]%MOD*ifac[n-i-1])%MOD;
    }
    cout << ans;
}