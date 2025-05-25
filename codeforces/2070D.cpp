#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<int> p(n,-1),dep(n);
    vector<vector<int>> id(n);
    vector<mint> dp(n);
    dp[0]=1;
    mint tot=0;
    for(int i=1;i<n;i++){
        cin >> p[i];
        p[i]--;
        dep[i]=dep[p[i]]+1;
        id[dep[i]].emplace_back(i);
        if(dep[i]==1){
            dp[i]=1;
            tot++;
        }
    }
    for(int d=2;d<n;d++){
        mint cur=0;
        for(auto i:id[d]){
            dp[i]=tot-dp[p[i]];
            cur+=dp[i];
        }
        tot=cur;
    }
    cout << accumulate(dp.begin(),dp.end(),mint(0)) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}