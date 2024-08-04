#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using namespace std;

using mint = mint998;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<vector<mint>> dp(n+1,vector<mint>(k+1));
    vector<mint> aux(k+1);
    dp[0][0]=aux[0]=1;
    for(int i=1;i<=n;i++){
        dp[i][1]=1;
        for(int j=1;j<=k;j++){
            auto &x=dp[i][min(j+1,k)];
            x+=aux[j];
            if(i>=2)x-=dp[i-2][j];
        }
        for(int j=1;j<=k;j++)aux[j]+=dp[i][j];
    }
    cout << dp[n][k]+dp[n-2][k]+dp[n-2][k-1];
}