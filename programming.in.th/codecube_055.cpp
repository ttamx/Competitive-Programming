#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int mod=9871;

int dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    dp[0][0]=1;
    for(int i=1;i<N;i++)for(int j=1;j<=i;j++)dp[i][j]=(dp[i-1][j-1]+dp[i-1][j]*j)%mod;
    int q;
    cin >> q;
    while(q--){
        int n,k;
        cin >> n >> k;
        cout << dp[n][k] << "\n";
    }
}