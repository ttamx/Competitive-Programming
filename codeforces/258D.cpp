#include<bits/stdc++.h>

using namespace std;

const int N=1005;

int n,m;
int a[N];
double dp[N][N];
double ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=a[i]>a[j];
        }
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        for(int j=1;j<=n;j++){
            if(j==u||j==v)continue;
            dp[j][u]=dp[j][v]=(dp[j][u]+dp[j][v])/2.0;
        }
        for(int j=1;j<=n;j++){
            if(j==u||j==v)continue;
            dp[u][j]=dp[v][j]=(dp[u][j]+dp[v][j])/2.0;
        }
        dp[u][v]=dp[v][u]=0.5;
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            ans+=dp[i][j];
        }
    }
    cout << fixed << setprecision(15) << ans << "\n";
}