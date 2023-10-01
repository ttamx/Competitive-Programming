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
    for(int i=0;i<1<<n;i++){
        int cnt=0;
        for(int j=0;j<n;j++)cnt+=i>>j&1;
        for(int j=0;j<n;j++){
            if(i>>j&1||!a[cnt][j])continue;
            dp[i|1<<j]+=dp[i];
            dp[i|1<<j]%=mod;
        }
    }
    cout << dp[(1<<n)-1];
}