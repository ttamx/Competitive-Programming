#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int MOD=1e9+7;

ll modpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

ll fac[N],ifac[N];

ll C(int n,int r){
    if(n<0||r<0||n<r)return 0LL;
    return fac[n]*ifac[n-r]%MOD*ifac[r]%MOD;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    fac[0]=1;
    for(int i=1;i<N;i++)fac[i]=fac[i-1]*i%MOD;
    ifac[N-1]=modpow(fac[N-1],MOD-2);
    for(int i=N-1;i>=1;i--)ifac[i-1]=ifac[i]*i%MOD;
    int t;
    cin >> t;
    while(t--){
        int n,m,k;
        cin >> n >> m >> k;
        vector<ll> pw(n+1);
        pw[0]=1;
        for(int i=1;i<=n;i++)pw[i]=pw[i-1]*m%MOD;
        ll cols=k;
        ll ans=0;
        for(int i=1;i<=n;i++){
            ll res=C(n-1,i-1)*cols%MOD*C(m-1+i,i)%MOD*pw[n-i]%MOD;
            ans=(ans+res)%MOD;
            cols=cols*(k-1)%MOD;
        }
        cout << ans << "\n";
    }
}