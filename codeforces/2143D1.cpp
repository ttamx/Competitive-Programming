#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<mint>> dp(n+1,vector<mint>(n+1));
    dp[0][0]=1;
    for(auto x:a){
        auto ndp=dp;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                if(x>=j){
                    ndp[i][x]+=dp[i][j];
                }else if(x>=i){
                    ndp[x][j]+=dp[i][j];
                }
            }
        }
        dp=move(ndp);
    }
    mint ans=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            ans+=dp[i][j];
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}