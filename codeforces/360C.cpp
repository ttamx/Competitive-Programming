#include "template.hpp"
#include "modular-arithmetic/modint.hpp"

using mint = mint107;

void runcase(){
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    vv(mint,dp,n+1,k+1);
    vv(mint,dp2,n+1,k+1);
    dp[0][0]=1;
    mint ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<=k;j++){
            dp[i+1][j]+=(dp[i][j]+dp2[i][j])*(s[i]-'a');
            dp2[i+1][j]+=dp[i][j]+dp2[i][j];
            if(j+n-i>k)continue;
            for(int x=i;x<n;x++){
                dp[x+1][j+n-i]+=dp[i][j]*('z'-s[x]);
            }
        }
    }
    cout << dp[n][k]+dp2[n][k] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}