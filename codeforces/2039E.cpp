#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    if(n==2){
        cout << 1 << "\n";
        return;
    }
    if(n==3){
        cout << 2 << "\n";
        return;
    }
    vector<mint> dp(n+1);
    mint add=0,ans=0;
    for(int i=3;i<=n;i++){
        dp[i]+=add;
        add+=dp[i]*i;
        add+=i-1;
        ans+=dp[i];
    }
    cout << ans+n-1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}