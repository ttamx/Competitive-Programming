#include<bits/stdc++.h>

using namespace std;

const int N=5005;

typedef long long ll;

ll n,p;
ll fac[N],inv[N],dp[N];

ll binpow(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1)ret=(ret*a)%p;
        a=(a*a)%p;
        b>>=1;
    }
    return ret;
}

ll C(int n,int r){
    return (((fac[n]*inv[n-r])%p)*inv[r])%p;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p;
    fac[0]=1;
    inv[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%p;
        inv[i]=binpow(fac[i],p-2);
    }
    ll ans=0,sum=0;
    for(int i=n/2;i>0;i--){
        if(i==1)dp[i]=1;
        else for(int j=i;j<=n/2;j++)dp[i]=(dp[i]+C(j-i,i-2))%p;
        dp[i]=(dp[i]*fac[n-i])%p;
        ans=(ans+((dp[i]-sum+p)%p))%p;
        cout << (dp[i]-sum+p)%p << '\n';
        sum+=dp[i];
    }
    cout << ans;
}