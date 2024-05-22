#include<bits/stdc++.h>

using namespace std;

const int N=25;
const int K=(1<<21)+5;
const int MOD=1e9+7;

int n;
int a[N][N];
int dp[K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> a[i][j];
        }
    }
    dp[0]=1;
    for(int mask=1;mask<(1<<n);mask++){
        int cnt=__builtin_popcount(mask);
        for(int i=1;i<=n;i++){
            if(((mask>>(i-1))&1)==1&&a[cnt][i]==1){
                int mask2=mask^(1<<(i-1));
                dp[mask]+=dp[mask2];
                dp[mask]%=MOD;
            }
        }
    }
    cout << dp[(1<<n)-1];
}