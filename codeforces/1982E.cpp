#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int K=65;

mint pw[K];
bool vis[K][K];
mint dp[K][K];

mint solve(int i,int j){
    if(j<0)return 0;
    if(vis[i][j])return dp[i][j];
    vis[i][j]=true;
    if(i==0){
        return dp[i][j]=1;
    }
    if(j>=i)return dp[i][j]=pw[i]*(pw[i]+1)/2;
    if(j==i-1)return dp[i][j]=pw[i]*(pw[i]-1)/2;
    return dp[i][j]=solve(i-1,j)+solve(i-1,j-1);
}

mint solve2(ll n,int k){
    if(k<0||n<1)return 0;
    if(n==1)return 1;
    int i=63-__builtin_clzll(n);
    if(k>=i)return mint(n)*mint(n+1)/2;
    return solve(i,k)+solve2(n-(1LL<<i),k-1);
}

void runcase(){
    ll n;
    int k;
    cin >> n >> k;
    cout << solve2(n,k) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    pw[0]=1;
    for(int i=1;i<K;i++)pw[i]=pw[i-1]*2;
    int t(1);
    cin >> t;
    while(t--)runcase();
}