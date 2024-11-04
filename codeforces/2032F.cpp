#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto b=a;
    for(int i=n-2;i>=0;i--){
        b[i]^=b[i+1];
    }
    map<int,mint> loses,wins;
    vector<mint> wins2(2);
    mint sum_loses=0,sum_wins=0;
    mint ways=1;
    vector<mint> dp(n);
    loses[0]++;
    sum_loses++;
    for(int i=n-1,p=n-1;i>=0;i--){
        dp[i]+=sum_loses-loses[b[i]];
        if(a[i]==1){
            dp[i]+=wins2[i%2];
        }else{
            for(;p>i;p--){
                wins2[p%2]-=dp[p];
                wins[b[p]]+=dp[p];
                sum_wins+=dp[p];
            }
        }
        dp[i]+=sum_wins-wins[b[i]];
        mint lose=ways-dp[i];
        loses[b[i]]+=lose;
        sum_loses+=lose;
        wins2[i%2]+=dp[i];
        ways*=2;
    }
    cout << dp[0] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}