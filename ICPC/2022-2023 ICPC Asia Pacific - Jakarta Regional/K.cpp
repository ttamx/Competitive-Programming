#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const ll INF=1e30;
const int MOD=998244353;
const int MOD2=MOD-1;

int n,k;
ll a[N];

struct Jump{
    ll q,r;
    Jump(){}
    Jump(ll _q,ll _r):q(_q),r(_r){}
    Jump(ll x):q(x/n),r(x%n){}
    friend Jump operator*(const Jump &lhs,const Jump &rhs){
        Jump res;
        res.q=lhs.q*rhs.q%MOD2*n%MOD2;
        res.q+=lhs.q*rhs.r%MOD2;
        res.q+=rhs.q*lhs.r%MOD2;
        res.q+=lhs.r*rhs.r/n;
        res.q%=MOD2;
        res.r=lhs.r*rhs.r%n;
        return res;
    }
};

Jump monoid_pow(Jump base,ll k){
    if(k==1)return base;
    Jump x=monoid_pow(base,k/2);
    x=x*x;
    if(k&1)x=x*base;
    return x;
}

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
    cin >> n >> k;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    Jump jump=monoid_pow(Jump(2),k);
    ll q=jump.q,r=jump.r;
    ll base=1;
    for(int i=0;i<n;i++){
        base=base*a[i]%MOD;
    }
    base=modpow(base,q);
    for(int i=0;i<r;i++){
        base=base*a[i]%MOD;
    }
    for(int i=0;i<n;i++){
        cout << base << " ";
        base=base*modpow(a[i],MOD-2)%MOD;
        base=base*a[r]%MOD;
        r=(r+1)%n;
    }
}