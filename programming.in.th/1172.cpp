#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int mod=10001;

int n;
int dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    dp[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            dp[i]+=dp[j]*dp[i-j-1];
            dp[i]%=mod;
        }
    }
    cout << dp[n];
}