#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<bool> b(n+1);
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        b[x]=true;
    }
    vector<array<mint,2>> dp(n+1,{0,0});
    dp[0][1]=1;
    for(int i=1;i<=n;i++){
        dp[i][1]+=dp[i-1][0];
        if(!b[i]){
            dp[i][0]+=dp[i-1][0]*2+dp[i-1][1];
            dp[i][1]+=dp[i-1][1];
        }
    }
    cout << dp[n][0];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}