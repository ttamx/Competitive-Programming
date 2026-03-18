#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n+1);
    for(auto &x:a)cin >> x;
    ll tot=accumulate(a.begin(),a.end(),0LL);
    ll t=tot/n;
    for(int i=1;i<=n;i++){
        a[i]-=t;
        if(a[i]<0){
            a[0]+=a[i];
            a[i]=0;
        }
    }
    if(a[0]<0)return void(cout << "0\n");
    int c=0;
    for(int i=1;i<=n;i++){
        if(a[i]>1)return void(cout << "0\n");
        if(a[i]==1)c++;
    }
    cout << comb.C(n-c,a[0])*comb.fac(a[0]+c)*comb.fac(n-c-a[0]) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}