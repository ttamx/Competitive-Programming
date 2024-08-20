#include<bits/stdc++.h>

using namespace std;

using ll = long long;

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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    ll ans=1;
    for(int i=0;i<n;i++){
        ll a,b;
        cin >> a >> b;
        ll p=a*modpow((a+b)%MOD,MOD-2)%MOD;
        ll q=(MOD+1-p)%MOD;
        ans=(ans*p+(MOD+1-ans)*q)%MOD;
    }
    cout << ans;
}