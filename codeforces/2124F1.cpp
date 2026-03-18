#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n+1,vector<int>(n+1));
    for(int i=0;i<m;i++){
        int x,y;
        cin >> x >> y;
        a[x][y]=1;
    }
    vector<mint> dp(n+1);
    vector<vector<mint>> dp2(n+1,vector<mint>(n+1));
    // dp2[i][j] := fill 1..i and ends with [1...j] and the last step is [1..j]
    dp[0]=1;
    for(int i=0;i<n;i++){
        for(int s=1;i+s<=n;s++){
            if(a[i+s][s])break;
            dp[i+s]+=dp[i];
            dp2[i+s][s]+=dp[i];
        }
        for(int s=2;i+s<=n;s++){
            for(int r=2;r<=s;r++){
                int cur=r;
                bool ok=true;
                for(int j=1;j<=s;j++){
                    if(a[i+j][cur]){
                        ok=false;
                        break;
                    }
                    cur++;
                    if(cur>s)cur=1;
                }
                if(ok){
                    mint w=dp[i]-dp2[i][r-1];
                    dp[i+s]+=w;
                }
            }
        }
    }
    cout << dp[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}