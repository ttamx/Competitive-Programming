#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const ll MOD=1e9+7;

int n,q;
ll p,invp;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

struct Fenwick{
    ll t[N];
    void update(int i,ll v){
        for(;i<N;i+=i&-i){
            t[i]=(t[i]+v+MOD)%MOD;
        }
    }
    ll query(int i){
        ll res=0;
        for(;i>0;i-=i&-i){
            res=(res+t[i])%MOD;
        }
        return res;
    }
    ll query(int l,int r){
        if(l>r)return 0LL;
        return (query(r)-query(l-1)+MOD)%MOD;
    }
}fl,fr;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    double prob;
    cin >> prob;
    invp=binpow(ll((1-prob)*1e6+.5),MOD-2)*ll(1e6)%MOD;
    p=binpow(invp,MOD-2);
    while(q--){
        char op;
        cin >> op;
        if(op=='+'){
            ll b;
            int x;
            cin >> b >> x;
            fl.update(x,b*binpow(invp,x)%MOD);
            fr.update(x,b*binpow(p,x)%MOD);
        }else if(op=='-'){
            ll b;
            int x;
            cin >> b >> x;
            fl.update(x,-b*binpow(invp,x)%MOD);
            fr.update(x,-b*binpow(p,x)%MOD);
        }else{
            int x;
            cin >> x;
            cout << (fl.query(x)*binpow(p,x)+fr.query(x+1,n)*binpow(invp,x))%MOD << "\n";
        }
    }
}