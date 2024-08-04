#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

mint modpow(mint a,ll b){
    mint res=1;
    for(;b;b>>=1,a*=a)if(b&1)res*=a;
    return res;
}

void runcase(){
    int l,r,k;
    cin >> l >> r >> k;
    if(k>=10)return void(cout << 0 << "\n");
    mint x=9/k;
    mint ans=(modpow(x+1,r)-modpow(x+1,max(l,1)));
    if(l==0)ans+=x;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}