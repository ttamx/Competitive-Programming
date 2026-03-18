#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

const int N=22;

int n;
string t;
mint dp[1<<22];
bool vis[1<<22];

mint calc_dp(int mask){
    if(mask==0)return mint(1);
    if(vis[mask])return dp[mask];
    vis[mask]=true;
    mint cur=0;
    int pre=-1;
    for(int i=0;i<n;i++){
        if(!(mask>>i&1))continue;
        if(pre==-1||t[i]!=t[pre]){
            cur+=calc_dp(mask^(1<<i));
        }
        pre=i;
    }
    return dp[mask]=cur;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> t;
    cout << calc_dp((1<<n)-1) << "\n";
}