#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll p=1e9+7;

ll binpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n;
    cin >> n;
    ll ans=(n!=2);
    if(n%2==0){
        ans+=binpow(2,n/2);
        ans%=p;
    }
    cout << ans;
}