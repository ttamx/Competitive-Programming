#include<bits/stdc++.h>

using namespace std;

const int N=505;

int n;
int p[N],dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        p[x]=i;
    }
    for(int s=2;s<=n;s++)for(int l=1,r=s;r<=n;l++,r++){
        dp[l][r]=INT_MAX;
        for(int m=l;m<r;m++)dp[l][r]=min(dp[l][r],dp[l][m]+dp[m+1][r]+abs(p[l]-p[m+1]));
    }
    cout << dp[1][n];
}