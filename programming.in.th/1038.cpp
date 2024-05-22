#include<bits/stdc++.h>

using namespace std;

const int N=25;
const int K=1<<20;

int n;
double a[N][N],dp[K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> a[i][j];
            a[i][j]/=100;
        }
    }
    dp[0]=1;
    for(int mask=1;mask<1<<n;mask++){
        int cnt=__builtin_popcount(mask)-1;
        for(int i=0;i<n;i++){
            if(mask>>i&1){
                dp[mask]=max(dp[mask],dp[mask^(1<<i)]*a[cnt][i]);
            }
        }
    }
    cout << fixed << setprecision(12) << dp[(1<<n)-1]*100;
}