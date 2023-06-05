#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<vector<int>> dp(n+2,vector<int>(n+2)),dpl(n+2,vector<int>(n+2,-1e9)),dpr(n+2,vector<int>(n+2,-1e9));
    for(int i=1;i<=n;i++){
        int mx=0;
        for(int j=1;j<=n;j++){
            dp[i][j]=(a[j-1]<a[j]?dp[i][j-1]+1:1);
            for(int k=0;k<j;k++){
                if(a[k]>a[j])continue;
                dp[i][j]=max(dp[i][j],dp[i-1][k]+1);
            }
            mx=max(mx,dp[i-1][j]);
            
        }
        dpl[i][1]=dpr[i][n]=1;
        for(int j=2;j<=n;j++){
            dpl[i][j]=(a[j-1]<a[j]?dpl[i][j-1]+1:-1e9);
            for(int k=1;k<j;k++){
                if(a[k]>a[j])continue;
                dpl[i][j]=max(dpl[i][j],dpl[i-1][k]+1);
            }
        }
        for(int j=n-1;j>=1;j--){
            dpr[i][j]=(a[j]<a[j+1]?dpr[i][j+1]+1:-1e9);
            for(int k=n;k>j;k--){
                if(a[k]<a[j])continue;
                dpr[i][j]=max(dpr[i][j],dpr[i-1][k]+1);
            }
        }
        for(int j=1;j<=n;j++){
            mx=max(mx,dpl[i][j]);
            mx=max(mx,dpr[i][j]);
            for(int k=j+1;k<=n;k++){
                if(a[j]>a[k])continue;
                mx=max(mx,dpl[i][j]+dpr[1][k]);
            }
        }
        cout << n-mx << " \n"[i==n];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}