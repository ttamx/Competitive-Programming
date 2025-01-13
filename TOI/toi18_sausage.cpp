#include<bits/stdc++.h>

using namespace std;

const int N=5005;

int n;
int d[N],dp[N][N],dp2[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> d[i];
    }
    for(int sz=2;sz<=n;sz++){
        for(int l=1,r=sz;r<=n;l++,r++){
            dp[l][r]=max(dp[l][r-1],dp[l+1][r])+abs(d[l]-d[r]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            dp2[i]=max(dp2[i],dp2[j-1]+dp[j][i]);
        }
    }
    cout << dp2[n];
}