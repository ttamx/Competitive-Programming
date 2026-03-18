#include "template.hpp"
#include "modular-arithmetic/modint.hpp"

using mint = ModInt<0>;

void runcase(){
    int n,m,mod;
    cin >> n >> m >> mod;
    mint::set_mod(mod);
    vector<mint> cnt(n+1);
    for(int i=0;i<n;i++){
        cnt[min(i,n-i-1)]++;
    }
    for(int i=0;i+1<n;i++){
        cnt[min(i+1,n-i-1)]++;
    }
    for(int i=n;i>0;i--){
        cnt[i-1]+=cnt[i];
    }
    mint inv=mint(m).inv();
    vector<mint> pw(n+1),ipw(n+1);
    pw[0]=ipw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*m;
    for(int i=1;i<=n;i++)ipw[i]=ipw[i-1]*inv;
    mint ans=0;
    for(int i=1;i<=n;i++){
        ans+=cnt[i]*ipw[i]*mint(i)*mint(i+1)/2;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}