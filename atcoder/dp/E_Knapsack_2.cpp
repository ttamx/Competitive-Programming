#include<bits/stdc++.h>

using namespace std;

const int N=105;
const int V=100005;

int n,m;
int w[N],v[N],dp[N][V];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> w[i] >> v[i];
    for(int i=1;i<V;i++)dp[0][i]=m+1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<V;j++){
            dp[i][j]=dp[i-1][j];
            if(j>=v[i])dp[i][j]=min(dp[i][j],dp[i-1][j-v[i]]+w[i]);
        }
    }
    for(int i=V-1;i>=0;i--)if(dp[n][i]<=m)cout << i,exit(0);
}