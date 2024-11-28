#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int D=60;

void runcase(){
    int n;
    ll l,r,z;
    cin >> n >> l >> r >> z;
    vector<vector<mint>> C(n+1,vector<mint>(n+1));
    for(int i=0;i<=n;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
    auto calc=[&](ll v){
        vector<mint> dp(2*n+2);
        dp[0]=1;
        for(int i=0;i<60;i++){
            vector<mint> ndp(2*n+2);
            for(int j=0;j<=n+1;j++){
                for(int k=z>>i&1;k<=n;k+=2){
                    int cur=(j+k)%2;
                    int x=(j+k)/2+(cur>(v>>i&1));
                    ndp[x]+=dp[j]*C[n][k];
                }
            }
            dp=move(ndp);
        }
        return dp[0];
    };
    cout << calc(r)-calc(l-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}