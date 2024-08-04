#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> a(n+1,vector<int>(n+1));
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            cin >> a[i][j];
        }
    }
    for(int i=1;i<=n;i++)if(a[i][i]==2)return void(cout << "0\n");
    vector dp(n+1,vector<mint>(n+1));
    dp[1][1]=1;
    for(int i=2;i<=n;i++){
        bool ok=true;
        for(int j=1;j<i;j++){
            if(a[j][i]==1){
                ok=false;
                break;
            }
        }
        if(ok){
            for(int j=1;j<i;j++){
                dp[i][i]+=dp[i-1][j];
            }
        }
        for(int j=1;j<i;j++){
            ok=true;
            for(int k=1;k<j;k++){
                if(a[k][i]==1){
                    ok=false;
                    break;
                }
            }
            for(int k=j;k<i;k++){
                if(a[k][i]==2){
                    ok=false;
                    break;
                }
            }
            if(ok){
                dp[i][j]=dp[i-1][j];
            }
        }
    }
    mint ans=0;
    for(int i=1;i<=n;i++)ans+=dp[n][i];
    cout << ans*2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}