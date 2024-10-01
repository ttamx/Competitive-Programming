#include "template.hpp"
#include "modular-arithmetic/modint.hpp"

using mint = mint32;

void runcase(){
    int n,k,p;
    cin >> n >> k >> p;
    mint::set_mod(p);
    vector<vector<mint>> ways(n,vector<mint>(k+1));
    for(int i=0;i<=k;i++)ways[0][i]=1;
    for(int i=1;i<n;i++){
        for(int j=0;j<=k;j++){
            for(int x=0;x<=j;x++){
                ways[i][j]+=ways[i-1][x]*ways[i-1][j-x];
            }
            if(j>0){
                ways[i][j]+=ways[i][j-1];
            }
        }
    }
    vector<mint> dp(k+1);
    dp[k]=1;
    for(int i=n-2;i>=0;i--){
        vector<mint> ndp(k+1);
        auto aux=ways[i];
        for(int j=0;j<k;j++)aux[j+1]+=aux[j];
        for(int j=1;j<=k;j++){
            for(int x=j;x>=1;x--){
                ndp[x]+=dp[j]*aux[min(x-1,j-x)]*2;
            }
        }
        swap(dp,ndp);
    }
    cout << accumulate(dp.begin(),dp.end(),mint(0)) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}