#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

// (n - 1) * sum <= m * n
// sum - mn <= m

void runcase(){
    ll n,m;
    cin >> n >> m;
    if(n==1){
        cout << m << "\n";
        return;
    }
    if(m<n||n*(n+1)/2>m+1){
        cout << 0 << "\n";
        return;
    }
    m++;
    mint ans=0;
    vector<vector<mint>> dp(n+1,vector<mint>(m+1));
    dp[1][1]=1;
    for(int i=1;i<n;i++){
        for(int j=0;j<=m;j++){
            if(j+i<=m){
                dp[i][j+i]+=dp[i][j];
            }
            if(j+i+1<=m){
                dp[i+1][j+i+1]+=dp[i][j];
            }
        }
    }
    for(int i=1;i<=m;i++){
        ans+=dp[n][i]*(m-i+1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}