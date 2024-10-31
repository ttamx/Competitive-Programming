#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<vector<mint>> C(n+1,vector<mint>(n+1));
    for(int i=0;i<=n;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
    vector<vector<mint>> pw(k+1,vector<mint>(n*n+1));
    for(int i=1;i<=k;i++){
        pw[i][0]=1;
        for(int j=1;j<=n*n;j++){
            pw[i][j]=pw[i][j-1]*i;
        }

    }
    vector<vector<mint>> dp(n,vector<mint>(k+1));
    auto calc=[&](int n){
        return n*(n-1)/2;
    };
    dp[0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            dp[i][j+1]+=dp[i][j];
            for(int x=1;i+x<n;x++){
                dp[i+x][j+1]+=pw[k-j][max(calc(i+x+1)-calc(i+1)-x,0)]*C[n-i-1][x]*dp[i][j];
            }
        }
    }
    cout << dp[n-1][k] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}