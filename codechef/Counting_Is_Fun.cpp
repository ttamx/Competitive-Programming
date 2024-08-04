#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    if(n==1)return void(cout << 1 << "\n");
    if(n==2)return void(cout << 3 << "\n");
    vector<mint> dp(n+1),dp2(n+1);
    dp[1]=1;
    dp[2]=mint(3)/mint(2);
    dp[3]=mint(5)/mint(2);
    dp2[3]=mint(5)/mint(2);
    for(int i=4;i<=n;i++){
        dp2[i]=dp2[i-1]+dp[i-2];
        dp[i]=dp[i-1]+dp2[i];
    }
    mint ans=dp[n];
    for(int i=1;i<=n;i++)ans*=i;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}