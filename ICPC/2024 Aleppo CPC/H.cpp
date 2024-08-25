#include<bits/stdc++.h>

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

void runcase(){
    int n;
    cin >> n;
    ll ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+binpow(i+1,MOD-2))%MOD;
    }
    ans=(ans*(n+1))%MOD;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}