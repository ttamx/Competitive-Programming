#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<mint> dp(k+1);
    dp[0]=1;
    reverse(s.begin(),s.end());
    for(auto x:s){
        auto ndp=dp;
        for(int j=0;j<=k;j++){
            for(int t=1;j+t<=k;t++){
                int p=(j+t+(x=='0'))/2;
                if(t<=p){
                    ndp[j+t]+=dp[j]*comb.C(p,t);
                }
            }
        }
        dp=move(ndp);
    }
    cout << dp[k] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}