#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD=1e6+3;

ll mul(ll a,ll b){
    return (a*b)%MOD;
}

ll binpow(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1)ret=mul(ret,a);
        a=mul(a,a);
        b>>=1;
    }
    return ret;
}

ll inv(int a){
    return binpow(a,MOD-2);
}

ll pi(ll a,ll b){
    ll ret=1;
    while(a<=b)ret=mul(ret,a++);
    return ret;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll a,b;
    cin >> a >> b;
    cout << mul(pi(b+1,a),inv(pi(1,a-b)));
}