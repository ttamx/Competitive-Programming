#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
ll dp[25][2];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    dp[0][0]=1;
    for(int i=1;i<=24;i++){
        dp[i][0]=dp[i-1][0]+dp[i-1][1]+1;
        dp[i][1]=dp[i-1][0];
    }
    while(true){
        cin >> n;
        if(n==-1)break;
        cout << dp[n][0] << " " << dp[n][0]+dp[n][1]+1 << "\n";
    }
}