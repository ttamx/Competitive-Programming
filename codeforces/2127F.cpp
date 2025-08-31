#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

mint calc(int n,int mx,int sum){
    mint res=0;
    for(int i=0;i<=n&&i*(mx+1)<=sum;i++){
        mint cur=comb.C(n,i)*comb.C(sum-i*(mx+1)+n-1,n-1);
        if(i%2==0)res+=cur;
        else res-=cur;
    }
    return res;
}

void runcase(){
    int n,m;
    cin >> n >> m;
    mint ans=0;
    for(int mx=1;mx<=m;mx++){
        ans+=(mint(mx)-mint(m-mx)*comb.inv(n-1))*calc(n-1,mx,m-mx);
    }
    if(n>2){
        for(int mx=1;mx*2<=m;mx++){
            ans+=(mint(mx)*mint(n-2)-mint(m-mx*2))*calc(n-2,mx,m-mx*2);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}