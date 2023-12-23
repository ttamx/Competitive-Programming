#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2005;
const int mod=1e9+7;

int n,s,e;
ll dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> s >> e;
    dp[1][1]=1;
    int cnt=2;
    for(int i=1;i<=n;i++){
        if(i==s||i==e){
            for(int j=1;j<i;j++){
                dp[i][j+1]+=dp[i-1][j];
                dp[i][j+1]%=mod;
                dp[i][j]+=dp[i-1][j];
                dp[i][j]%=mod;
            }
            cnt--;
            continue;
        }
        for(int j=1;j<i;j++){
            dp[i][j+1]+=dp[i-1][j]*(cnt+j-1)%mod;
            dp[i][j+1]%=mod;
            dp[i][j-1]+=dp[i-1][j]*(j-1)%mod;
            dp[i][j-1]%=mod;
        }
    }
    cout << dp[n][1];
}