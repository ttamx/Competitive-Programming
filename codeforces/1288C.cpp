#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<mint> dp(n);
    dp[0]=1;
    for(int i=0;i<m;i++){
        for(int j=1;j<n;j++){
            dp[j]+=dp[j-1];
        }
    }
    mint ans=0;
    for(int l=0;l<n;l++){
        for(int r=l;r<n;r++){
            ans+=dp[l]*dp[n-r-1];
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}