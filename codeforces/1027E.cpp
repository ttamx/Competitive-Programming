#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<vector<mint>> dp(n+1,vector<mint>(n+1));
    dp[1][0]=1;
    for(int i=0;i<n;i++){
        vector<vector<mint>> ndp(n+1,vector<mint>(n+1));
        for(int j=1;j<=n;j++){
            for(int k=0;k<=n;k++){
                ndp[j][1]+=dp[j][k];
                if(k+1<=n)ndp[max(j,k+1)][k+1]+=dp[j][k];
            }
        }
        dp=move(ndp);
    }
    mint ans=0;
    for(int i=1;i<=n;i++){
        mint ways=0;
        for(int j=0;j<=n;j++){
            ways+=dp[i][j];
        }
        int t=(k-1)/i;
        if(!t)continue;
        vector<mint> dp2(n+1),sum(n+1);
        dp2[0]=sum[0]=1;
        for(int i=1;i<=n;i++){
            dp2[i]=sum[i-1]-(i>t?sum[i-t-1]:mint(0));
            sum[i]=sum[i-1]+dp2[i];
        }
        ans+=dp2[n]*ways;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}