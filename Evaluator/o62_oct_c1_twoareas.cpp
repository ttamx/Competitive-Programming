#include<bits/stdc++.h>

using namespace std;

const int N=305;
const int inf=2e9;

int n,m;
int a[N][N];
int dp1[N][N][N],dp2[N][N][N];

int solve(){
    int ans=-inf;
    for(int i=1;i<=m;i++)for(int j=i;j<=m;j++)dp1[0][i][j]=dp2[0][i][j]=-inf;
    for(int i=1;i<=m;i++)for(int j=i;j<=m;j++)dp1[n+1][i][j]=dp2[n+1][i][j]=-inf;
    for(int i=1;i<=n;i++){
        for(int l=1;l<=m;l++){
            int sum=0;
            for(int r=l;r<=m;r++){
                sum+=a[i][r];
                dp1[i][l][r]=sum+max(0,dp1[i-1][l][r]);
            }
        }
    }
    for(int i=n;i>=1;i--){
        for(int l=1;l<=m;l++){
            int sum=0;
            for(int r=l;r<=m;r++){
                sum+=a[i][r];
                dp2[i][l][r]=sum+max(0,dp2[i+1][l][r]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(i<=n-2)for(int l=1;l<=m;l++)ans=max(ans,dp1[i][l][l]+dp2[i+2][l][l]);
        for(int sz=2;sz<=m;sz++){
            for(int l=1,r=sz;r<=m;l++,r++){
                dp1[i][l][r]=max({dp1[i-1][l][r],dp1[i][l][r-1],dp1[i][l+1][r],dp1[i][l][r]});
                if(i<=n-2)ans=max(ans,dp1[i][l][r]+dp2[i+2][l][r]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int l=1;l<=m;l++){
            int sum=0;
            for(int r=l;r<=m;r++){
                sum+=a[i][r];
                dp1[i][l][r]=sum+max(0,dp1[i-1][l][r]);
            }
        }
    }
    for(int i=n;i>=1;i--){
        if(i>=3)for(int l=1;l<=m;l++)ans=max(ans,dp2[i][l][l]+dp1[i-2][l][l]);
        for(int sz=2;sz<=m;sz++){
            for(int l=1,r=sz;r<=m;l++,r++){
                dp2[i][l][r]=max({dp2[i+1][l][r],dp2[i][l][r-1],dp2[i][l+1][r],dp2[i][l][r]});
                if(i>=3)ans=max(ans,dp2[i][l][r]+dp1[i-2][l][r]);
            }
        }
    }
    return ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin >> a[i][j];
    int ans=solve();
    swap(n,m);
    for(int i=1;i<=max(m,n);i++)for(int j=1;j<i;j++)swap(a[i][j],a[j][i]);
    ans=max(ans,solve());
    cout << ans;
}