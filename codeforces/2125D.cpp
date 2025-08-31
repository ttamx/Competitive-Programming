#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> m >> n;
    mint base=1;
    vector<vector<pair<int,mint>>> a(n+1);
    for(int i=0;i<m;i++){
        int l,r;
        mint p,q;
        cin >> l >> r >> p >> q;
        a[l].emplace_back(r,p/q);
        base*=1-p/q;
    }
    vector<mint> dp(n+1);
    dp[0]=base;
    for(int i=1;i<=n;i++){
        for(auto [j,p]:a[i]){
            dp[j]+=dp[i-1]*p/(1-p);
        }
    }
    cout << dp[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}