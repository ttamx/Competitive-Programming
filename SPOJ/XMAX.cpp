#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct gauss{
    int n,sz;
    vector<ll> basis;
    gauss(int n=0){
        init(n);
    }
    void init(int _n){
        n=_n,sz=0;
        basis.assign(n,0);
    }
    void insert(ll x){
        for(int i=n-1;i>=0;i--)if(x>>i&1){
            if(!basis[i]){
                basis[i]=x;
                sz++;
                return;
            }
            x^=basis[i];
        }
    }
    ll getmax(ll k=0){
        ll tot=1ll<<sz,res=0;
        for(int i=n-1;i>=0;i--)if(basis[i]){
            tot>>=1;
            if((k>=tot&&res>>i&1)||(k<tot&&res>>i&1^1))res^=basis[i];
            if(k>=tot)k-=tot;
        }
        return res;
    }
}g;

int n;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    g.init(60);
    for(int i=0;i<n;i++){
        ll x;
        cin >> x;
        g.insert(x);
    }
    cout << g.getmax();
}