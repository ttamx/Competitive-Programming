#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=1000000007;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    array<array<array<ll,2>,2>,3> dp{};
    dp[0][a[0]][0]=1;
    for(int i=1;i<n;i++){
        array<array<array<ll,2>,2>,3> ndp{};
        for(int j=0;j<2;j++){
            ndp[0][j&a[i]][0]+=dp[0][j][0];
            ndp[0][j|a[i]][0]+=dp[0][j][0];
            ndp[0][j^a[i]][0]+=dp[0][j][0];
            ndp[1][j][a[i]]+=dp[0][j][0];
            ndp[2][j&a[i]][0]+=dp[2][j][0];
            ndp[2][j|a[i]][0]+=dp[2][j][0];
            ndp[2][j^a[i]][0]+=dp[2][j][0];
            for(int k=0;k<2;k++){
                ndp[1][j][k&a[i]]+=dp[1][j][k];
                ndp[1][j][k|a[i]]+=dp[1][j][k];
                ndp[1][j][k^a[i]]+=dp[1][j][k];
            }
        }
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                ndp[2][j&k][0]+=ndp[1][j][k];
                ndp[2][j|k][0]+=ndp[1][j][k];
                ndp[2][j^k][0]+=ndp[1][j][k];
            }
        }
        for(int t=0;t<3;t++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    ndp[t][j][k]%=MOD;
                }
            }
        }
        dp=move(ndp);
    }
    cout << (dp[0][1][0]*n+dp[2][1][0])%MOD << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}