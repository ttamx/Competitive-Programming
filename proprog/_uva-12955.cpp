#include<bits/stdc++.h>

using namespace std;

int fac[9];
int dp[100001];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    fac[0]=1;
    for(int i=1;i<9;i++)fac[i]=fac[i-1]*i;
    dp[0]=0;
    for(int i=1;i<=100000;i++){
        dp[i]=2e9;
        for(int j=1;j<9;j++)if(i>=fac[j])dp[i]=min(dp[i],dp[i-fac[j]]+1);
    }
    while(cin >> n){
        if(n==0)break;
        cout << dp[n] << '\n';
    }
}