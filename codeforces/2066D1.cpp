#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint107;

Combinatorics<mint> comb;

void runcase(){
    int n,c,m;
    cin >> n >> c >> m;
    vector<int> a(m);
    for(auto &x:a){
        cin >> x;
    }
    vector<mint> dp(m+1);
    dp[c]=1;
    for(int i=2;i<=n;i++){
        auto ndp=dp;
        for(int j=0;j<=m;j++){
            for(int k=max(1,c-j);k<=c&&j+k<=m;k++){
                ndp[j+k]+=dp[j]*comb.C(c,k);
            }
        }
        dp=move(ndp);
    }
    cout << dp[m] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}