#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<mint> dp(n+1);
    dp[0]=dp[1]=1;
    for(int i=2;i<=n;i++){
        mint pre=1;
        for(int j=1;j<=min(k,i-1);j++){
            pre*=(i-j+1);
            pre/=j;
            dp[i]+=dp[j]*dp[i-j]*2;
            if(j<min(k,i-1))dp[i]-=dp[j]*dp[i-j-1]*2;
            // if(j<k)dp[i]-=dp[i-j-1];
        }
        cerr << dp[i] << " \n"[i==n];
    }
    cout << dp[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}