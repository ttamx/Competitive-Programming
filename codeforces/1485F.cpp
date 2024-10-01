#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n;
    cin >> n;
    map<ll,mint> dp;
    dp[0]=1;
    ll cur=0;
    mint all=1;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mint res=all;
        all+=res-dp[cur];
        dp[cur]=res;
        cur+=x;
    }
    cout << all << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}