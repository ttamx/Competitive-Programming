#include<bits/stdc++.h>

using namespace std;

const int N=25;
const int K=(1<<21)+5;
const int mod=1e9+7;

int n;
int a[N][N];
int dp[K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin >> a[i][j];
    dp[0]=1;
    for(int i=1;i<1<<n;i++){
        int cnt=__builtin_popcount(i);
        for(int j=0;j<n;j++){
            if((i>>j&1)==1&&a[cnt-1][j]==1){
                dp[i]+=dp[i^(1<<j)];
                dp[i]%=mod;
            }
        }
    }
    cout << dp[(1<<n)-1];
}