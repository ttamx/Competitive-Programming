#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int M=3000;

int n;
int a[N];
int dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            dp[i][j]=M+1;
        }
    }
    for(int j=0;j<=n;j++){
        dp[0][j]=0;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(dp[i-1][j]<a[i]){
                dp[i][j]=min(dp[i][j],a[i]);
            }
            if(j>0){
                dp[i][j]=min(dp[i][j],dp[i-1][j-1]+1);
            }
        }
    }
    for(int j=0;j<=n;j++){
        if(dp[n][j]<=M){
            cout << j << "\n";
            exit(0);
        }
    }
    assert(false);
}