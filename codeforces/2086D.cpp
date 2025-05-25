#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n=26;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int s=accumulate(a.begin(),a.end(),0);
    int h1=s/2,h2=s-h1;
    int t=0;
    vector<mint> dp(h1+1);
    dp[0]=1;
    for(auto x:a){
        if(!x)continue;
        vector<mint> ndp(h1+1);
        for(int i=0;i<=h1;i++){
            if(i+x<=h1)ndp[i+x]+=dp[i]*comb.C(h1-i,x);
            if(t-i+x<=h2)ndp[i]+=dp[i]*comb.C(h2-(t-i),x);
        }
        t+=x;
        dp=move(ndp);
    }
    cout << dp.back() << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}