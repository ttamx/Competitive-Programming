#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int B=60;
const ll MOD=1e9+7;
const ll INV=5e8+4;

struct Basis{
    ll basis[B];
    ll mask[B];
    ll need=0;
    bool insert(ll v){
        ll cur=0;
        for(int i=B-1;i>=0;i--)if(v>>i&1){
            if(!basis[i]){
                basis[i]=v;
                mask[i]=cur|(1LL<<i);
                need|=1LL<<i;
                return true;
            }
            v^=basis[i];
            cur^=mask[i];
        }
        need&=~cur;
        return false;
    }
}bs;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    ll cur=1,tot=1;
    for(int i=1;i<=n;i++){
        ll x;
        cin >> x;
        tot=tot*2%MOD;
        if(!bs.insert(x))cur=cur*2%MOD;
        ll ans=(i+__builtin_popcountll(bs.need))*cur%MOD*INV%MOD;
        cout << (tot-ans+MOD)%MOD << "\n";
    }
}