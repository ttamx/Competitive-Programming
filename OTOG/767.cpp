#include<bits/stdc++.h>

using namespace std;

const int INF=1e9;

void runcase(){
    int m,d1,d2,d3;
    cin >> m >> d1 >> d2 >> d3;
    d1-=m,d2-=m,d3-=m;
    int na,nb,nc;
    cin >> na;
    vector<int> a(na);
    for(auto &x:a)cin >> x;
    a.emplace_back(-1);
    cin >> nb;
    vector<int> b(nb);
    for(auto &x:b)cin >> x;
    b.emplace_back(-2);
    cin >> nc;
    vector<int> c(nc);
    for(auto &x:c)cin >> x;
    c.emplace_back(-3);
    vector<vector<vector<int>>> dp(na+2,vector<vector<int>>(nb+2,vector<int>(nc+2,-INF)));
    dp[na][nb][nc]=0;
    for(int i=na;i>=0;i--){
        for(int j=nb;j>=0;j--){
            for(int k=nc;k>=0;k--){
                if(i==na&&j==nb&&k==nc)continue;
                if(a[i]==b[j]&&a[i]==c[k]){
                    dp[i][j][k]=dp[i+1][j+1][k+1]+d3;
                }else if(a[i]==b[j]){
                    dp[i][j][k]=max(dp[i+1][j+1][k]+d2,dp[i][j][k+1]+d1);
                }else if(a[i]==c[k]){
                    dp[i][j][k]=max(dp[i+1][j][k+1]+d2,dp[i][j+1][k]+d1);
                }else if(b[j]==c[k]){
                    dp[i][j][k]=max(dp[i][j+1][k+1]+d2,dp[i+1][j][k]+d1);
                }else{
                    dp[i][j][k]=max({dp[i+1][j][k],dp[i][j+1][k],dp[i][j][k+1]})+d1;
                }
            }
        }
    }
    cout << dp[0][0][0] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}