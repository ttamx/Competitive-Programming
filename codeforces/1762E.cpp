#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod=998244353;
const int N=5e5+5;

int n;
ll fac[N],inv[N],tree[N];

ll binpow(ll a,ll b){
    if(a==1)return a;
    ll res=1;
    while(b){
        if(b&1)res=(res*a)%mod;
        b>>=1;
        a=(a*a)%mod;
    }
    return res;
}

ll C(ll n,ll r){
    return (((fac[n]*inv[n-r])%mod)*inv[r])%mod;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    if(n&1){
        cout << 0;
        return 0;
    }
    tree[0]=fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%mod;
        inv[i]=binpow(fac[i],mod-2);
        tree[i]=binpow(i,i-2);
    }
    ll ans=0;
    for(int l=1;l<n;l++){
        int r=n-l;
        ll tmp=C(n-2,l-1);
        tmp=(tmp*l)%mod;
        tmp=(tmp*r)%mod;
        tmp=(tmp*tree[l])%mod;
        tmp=(tmp*tree[r])%mod;
        if(l&1)ans=(ans+mod-tmp)%mod;
        else ans=(ans+tmp)%mod;
    }
    cout << ans;
}