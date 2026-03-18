#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n+1);
    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        a[r]=max(a[r],l);
    }
    vector<mint> dp(n+1);
    dp[0]=dp[1]=1;
    int p=0;
    for(int i=2;i<=n;i++){
        dp[i]=dp[i-1]*2;
        while(p<a[i]){
            dp[i]-=dp[p];
            p++;
        }
    }
    cout << dp[n]*2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}