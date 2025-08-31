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
    vector<vector<int>> last(n+1,vector<int>(n+1));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            last[i][j]=i;
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=n;j>=1;j--){
            if(!a[i][j]){
                last[i-1][j-1]=last[i][j];
            }else{
                last[i][j]=0;
            }
        }
    }
    vector<mint> dp(n+2);
    vector<vector<mint>> dp2(n+2,vector<mint>(n+2));
    // dp2[i][j] := fill 1..i and the last step is [1..j]
    vector<vector<mint>> aux(n+2,vector<mint>(n+2));
    // aux[i][j] := fill 1..i and ends with [j..s] -> need to fill [1..j - 1]
    dp[0]=1;
    for(int i=0;i<n;i++){
        if(i>0){
            for(int j=1;j<=n;j++){
                aux[i][j]+=aux[i-1][j];
            }
        }
        for(int j=2;j<=n;j++){
            int e=last[i+1][1];
            if(e<i+j-1)continue;
            dp[i+j-1]+=aux[i][j];
        }
        for(int s=1;i+s<=n;s++){
            if(a[i+s][s])break;
            dp[i+s]+=dp[i];
            dp2[i+s][s]+=dp[i];
        }
        for(int r=2;r<=n;r++){
            int e=last[i+1][r];
            if(!e)continue;
            mint w=dp[i]-dp2[i][r-1];
            aux[i+1][r]+=w;
            aux[e+1][r]-=w;
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