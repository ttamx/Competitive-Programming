#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<mint> ways(m+1);
    ways[0]=1;
    for(int i=0;i<m;i++){
        vector<mint> nways(m+1);
        for(int i=0;i<=m;i++){
            if(i<m)nways[i+1]+=ways[i];
            if(i>0)nways[i-1]+=ways[i];
        }
        ways=move(nways);
    }
    vector<mint> dp(m+1);
    dp[0]=1;
    for(int i=2;i<=n;i++){
        vector<mint> ndp(m+1);
        for(int j=0;j<=m;j++){
            for(int k=0;j+k<=m;k++){
                ndp[j+k]+=dp[j]*ways[k];
            }
        }
        dp=move(ndp);
    }
    mint ans=0;
    for(int i=0;i<=m;i+=2){
        ans+=dp[i]*ways[i];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}