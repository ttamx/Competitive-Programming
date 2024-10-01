#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> p(q+1),v(q+1);
    for(int i=1;i<=q;i++){
        cin >> p[i] >> v[i];
    }
    vector<array<mint,2>> dp(q+1,{1,0});
    for(int i=1;i<=q;i++){
        vector<array<mint,2>> ndp(q+1,{0,0});
        for(int j=0;j<=q;j++){
            for(int k=0;k<2;k++){
                if(v[i]>=v[i-1]){
                    ndp[i][k]+=dp[j][k];
                }
                if(v[i]>=v[j]){
                    ndp[i][k^1]+=dp[j][k];
                }
            }
        }
        swap(dp,ndp);
    }
    mint ans=0;
    for(int i=0;i<=q;i++){
        for(int j=0;j<2;j++){
            ans+=dp[i][j];
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}