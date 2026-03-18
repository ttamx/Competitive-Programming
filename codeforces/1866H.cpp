#include<bits/stdc++.h>

using namespace std;

const int MOD=998244353;

using ll = long long;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<ll> fac(n+1),ifac(n+1),inv(n+1);
    fac[0]=1;
    ifac[0]=1;
    inv[1]=1;
    for(int i=2;i<=n;i++){
        inv[i]=MOD-1LL*(MOD/i)*inv[MOD%i]%MOD;
    }
    for(int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i%MOD;
        ifac[i]=ifac[i-1]*inv[i]%MOD;
    }
    ll ans=1,pre=1;
    for(int i=1;i<=min(n,k);i++){
        ll cur=binpow(i+1,k-i+1)*fac[i]%MOD;
        ans+=(cur-pre+MOD)*fac[n]%MOD*ifac[n-i]%MOD;
        pre=cur;
    }
    cout << ans%MOD << "\n";
}