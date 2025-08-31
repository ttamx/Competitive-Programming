#include "template.hpp"
#include "modular-arithmetic/modint.hpp"

using mint = mint32;

void runcase(){
    int n,m;
    cin >> n >> m;
    mint::set_mod(m);
    mint ans=0;
    vector<mint> fac(n+2);
    fac[0]=1;
    for(int i=1;i<=n+1;i++){
        fac[i]=fac[i-1]*i;
    }
    vector<mint> dp(n+1);
    dp[0]=1;
    for(int i=n;i>=1;i--){
        for(int j=n;j>=1;j--){
            dp[j]+=dp[j-1]*(n-i+1-(j-1))*i;
        }
    }
    cout << accumulate(dp.begin(),dp.end(),mint(0)) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}