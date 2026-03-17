#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=10007;

ll binpow(ll a,ll b,ll mod){
    ll res=1%mod;
    while(b>0){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

ll f(ll d,ll mod){
    if(d==1)return 1%mod;
    ll res=0;
    if(d%2)res=binpow(10,d-1,mod);
    ll v=f(d/2,mod);
    return (res+v+v*binpow(10,d/2,mod))%mod;
}

ll calc(vector<pair<ll,ll>> a,ll mod){
    ll res=0;
    for(auto [x,y]:a){
        res=(res*binpow(10,y,mod)+x*f(y,mod)%mod)%mod;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int m,k;
    cin >> k >> m;
    vector<pair<ll,ll>> a(k);
    for(auto &[x,y]:a)cin >> x >> y;
    ll n=calc(a,MOD);
    n=(n-calc(a,m)%MOD+MOD)%MOD;
    cout << n*binpow(m,MOD-2,MOD)%MOD << "\n";
}