#include<bits/stdc++.h>

using namespace std;

const int N=2005;
const int MOD=100999;

int dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<N;i++)dp[0][i]=1;
    for(int i=1;i<N;i++){
        for(int j=1;j<=i;j++)dp[i][j]=dp[i-j][j-1];
        for(int j=1;j<N;j++)if((dp[i][j]+=dp[i][j-1])>=MOD)dp[i][j]-=MOD;
    }
    int t;
    cin >> t;
    while(t--){
        int x;
        cin >> x;
        cout << dp[x][x] << "\n";
    }
}