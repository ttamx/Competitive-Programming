#include <bits/stdc++.h>
using namespace std;

using ll = long long;

signed main() {
    int n;
    cin >> n;
    vector a(n,vector(n,vector<ll>(n)));
    for(auto &x:a){
        for(auto &y:x){
            for(auto &z:y){
                cin >> z;
            }
        }
    }
    int b=1<<n;
    vector dp(b,vector<ll>(b,1e18));
    dp[0][0]=0;
    for(int i=1;i<b;i++){
        for(int j=1;j<b;j++){
            int c=__builtin_popcount(i)-1;
            if(c!=__builtin_popcount(j)-1)continue;
            for(int x=0;x<n;x++){
                if(!(i>>x&1))continue;
                for(int y=0;y<n;y++){
                    if(!(j>>y&1))continue;
                    int ii=i^(1<<x);
                    int jj=j^(1<<y);
                    dp[i][j]=min(dp[i][j],dp[ii][jj]+a[c][x][y]);
                }
            }
        }
    }
    cout << dp[b-1][b-1];
}