#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const ll MOD=998244353;

int n;
ll r1[N],s1[N],p1[N],r2[N],s2[N],p2[N];
ll dp1[N],dp2[N],dp3[N];

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

ll inv(ll x){
    return binpow(x,MOD-2);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> r1[i] >> s1[i] >> p1[i];
    }
    for(int i=1;i<=n;i++){
        cin >> r2[i] >> s2[i] >> p2[i];
    }
    ll ans=0;
    dp3[0]=1;
    for(int i=1;i<=n;i++){
        ll t1=inv((r1[i]+s1[i]+p1[i])%MOD);
        ll t2=inv((r2[i]+s2[i]+p2[i])%MOD);
        r1[i]=r1[i]*t1%MOD;
        s1[i]=s1[i]*t1%MOD;
        p1[i]=p1[i]*t1%MOD;
        r2[i]=r2[i]*t2%MOD;
        s2[i]=s2[i]*t2%MOD;
        p2[i]=p2[i]*t2%MOD;
        ll pw1=(r1[i]*s2[i]+s1[i]*p2[i]+p1[i]*r2[i])%MOD;
        ll pw2=(r2[i]*s1[i]+s2[i]*p1[i]+p2[i]*r1[i])%MOD;
        ll pd=(1+2*MOD-pw1-pw2)%MOD;
        ans=(ans+dp1[i-1]*pd)%MOD;
        ll p=(dp1[i-1]+dp2[i-1]+dp3[i-1])%MOD;
        dp1[i]=pw1*p%MOD;
        dp2[i]=pw2*p%MOD;
        dp3[i]=dp3[i-1]*pd%MOD;
    }
    cout << ans;
}