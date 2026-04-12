#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = MontgomeryModInt<676767677>;

Combinatorics<mint> comb;

void runcase(){
    int n,m;
    cin >> n >> m;
    mint ans=0;
    function<void(int,int,int)> rec=[&](int l,int r,int d){
        if(r<l)return;
        int mid=(l+r)/2;
        ans+=d*comb.H(n,m);
        if(l>1)ans-=d*comb.H(n-(mid-l+1),m);
        if(r<n)ans-=d*comb.H(n-(r-mid+1),m);
        if(l>1&&r<n)ans+=d*comb.H(n-(r-l+2),m);
        rec(l,mid-1,d+1);
        rec(mid+1,r,d+1);
    };
    rec(1,n,1);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}