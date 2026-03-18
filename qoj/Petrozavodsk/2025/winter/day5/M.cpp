#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD=ll(1e18)+31;

ll binpow(ll a,ll b){
    ll res=1;
    for(;b>0;b>>=1,a=__int128_t(a)*a%MOD)if(b&1)res=__int128_t(res)*a%MOD;
    return res;
}

int main(){
    int n;
    cin >> n;
    n=1000000-n;
    ll v=300;
    for(int i=0;i<n;i++)v=binpow(42,v);
    cout << v << "\n";
}