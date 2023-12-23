#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3e6+5;
const int mod=1e9+7;

ll modpow(ll a,ll b){
    ll res=1;
    for(;b>0;a=a*a%mod,b>>=1)if(b&1)res=res*a%mod;
    return res;
}

int n,q;
ll a[N],b[4],fac[N],invfac[N],ans[N];

ll C(int n,int r){
    return fac[n]*invfac[r]%mod*invfac[n-r]%mod;
}

// P(x) = ((1+x)^(3n+3) - (1+x^3))/((1+x)^3 - 1)

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    fac[0]=1;
    for(int i=1;i<=3*n+3;i++)fac[i]=fac[i-1]*i%mod;
    invfac[3*n+3]=modpow(fac[3*n+3],mod-2);
    for(int i=3*n+3;i>=1;i--)invfac[i-1]=invfac[i]*i%mod;
    for(int i=0;i<=3*n+3;i++)a[i]=C(3*n+3,i);
    for(int i=0;i<=3;i++)b[i]=C(3,i),a[i]=(a[i]+mod-b[i])%mod;
    b[0]--;
    for(int i=3*n;i>=0;i--){
        ll c=a[i+3];
        ans[i]=c;
        for(int j=3;j>=0;j--)a[i+j]=(a[i+j]+mod-c*b[j]%mod)%mod;
    }
    while(q--){
        int x;
        cin >> x;
        cout << ans[x] << "\n";
    }
}