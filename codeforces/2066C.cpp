#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n;
    cin >> n;
    map<int,mint> dp;
    mint base=1;
    int lz=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mint new_base=dp[x^lz];
        dp[lz]=dp[x^lz]*2+base*3;
        dp[x^lz]=0;
        lz^=x;
        base=new_base;
    }
    mint ans=base;
    for(auto [_,v]:dp){
        ans+=v;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}