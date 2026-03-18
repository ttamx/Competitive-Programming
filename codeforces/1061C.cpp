#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int X=1e6+5;

vector<int> dv[X];
mint dp[X];

void runcase(){
    for(int i=X-1;i>=1;i--){
        for(int j=i;j<X;j+=i){
            dv[j].emplace_back(i);
        }
    }
    int n;
    cin >> n;
    dp[0]=1;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        for(auto d:dv[x]){
            dp[d]+=dp[d-1];
        }
    }
    cout << accumulate(dp+1,dp+X,mint(0)) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}