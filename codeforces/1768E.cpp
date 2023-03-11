#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3e6+5;

ll n,p;
ll fac[N],inv[N];

ll binpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}

ll C(ll n,ll r){
    return fac[n]*inv[n-r]%p*inv[r]%p;
}

void runcase(){
    cin >> n >> p;
    fac[0]=inv[0]=1;
    for(int i=1;i<=3*n;i++){
        fac[i]=fac[i-1]*i%p;
        inv[i]=binpow(fac[i],p-2);
    }
    ll ans=0;
    ll cnt1=((fac[2*n]*2%p)-fac[n]-1+p)%p;
    ll all=(fac[3*n]-1+p)%p;
    all=(all+p-cnt1)%p;;
    ans=(ans+cnt1)%p;
    ll cnt2=2*C(2*n,n)%p*fac[n]%p*fac[2*n]%p;
    for(int i=0;i<=n;i++){
        ll tmp=C(n,i);
        tmp=tmp*tmp%p*C(2*n-i,n)%p*fac[n]%p*fac[n]%p*fac[n]%p;
        cnt2=(cnt2-tmp+p)%p;
    }
    cnt2=(cnt2+p-cnt1-1)%p;
    all=(all+p-cnt2)%p;
    ans=(ans+2*cnt2)%p;
    ans=(ans+3*all)%p;
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}