#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    int X=n*10;
    vector<mint> zero(n+1);
    vector<vector<mint>> dp(n+1,vector<mint>(2*X+1));
    zero[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            for(int k=0;k<=2*X;k++)if(k!=a[j]&&k+a[i]>=0&&k+a[i]<=2*X){
                dp[i][k+a[i]]+=dp[i][j];
            }
            for(int k=j+1;k<i;k++){
                dp[i][a[i]+a[k]+X]+=dp[k][0]
            }
        }
    }
    mint ans=0;
    for(auto x:dp)ans+=x;
    cout << ans << "\n";
}