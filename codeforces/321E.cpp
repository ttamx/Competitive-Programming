#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=4005;
const int inf=1e9;

int n,k;
int a[N][N],qs[N][N],sum[N][N];
int dp[2][N];

void solve(int d,int l,int r,int optl,int optr){
    if(l>r)return;
    int mid=(l+r)/2;
    p2 res(inf,-1);
    for(int i=optl;i<=min(optr,mid);i++)res=min(res,p2(dp[d^1][i-1]+sum[i][mid],i));
    int opt;
    tie(dp[d][mid],opt)=res;
    solve(d,l,mid-1,optl,opt);
    solve(d,mid+1,r,opt,optr);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin >> a[i][j];
    for(int i=1;i<=n;i++)for(int j=i;j>=1;j--)qs[i][j]=a[i][j]+qs[i][j+1];
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)sum[i][j]=sum[i][j-1]+qs[j][i];
    for(int i=1;i<=n;i++)dp[1][i]=sum[1][i];
    for(int i=2;i<=k;i++)solve(i&1,1,n,1,n);
    cout << dp[k&1][n];
}