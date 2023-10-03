#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int C=1e5+5;
const int N=305;
const ll inf=1e18;

int c,n,m;
int a[C];
ll t[C];
ll dp[N][N];

bool chk(ll x){
    ll cur=0;
    for(int i=1;i<=c;i++){
        cur+=dp[a[i-1]][a[i]]*x;
        cur=max(cur,t[i-1]);
        if(cur>t[i])return false;
    }
    return true;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> c >> n >> m;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=inf;
    for(int i=1;i<=n;i++)dp[i][i]=0;
    for(int i=1;i<=c;i++)cin >> a[i];
    for(int i=1;i<=c;i++)cin >> t[i];
    for(int i=2;i<=c;i++)t[i]+=t[i-1];
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        dp[u][v]=dp[v][u]=w;
    }
    for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
    int l=0,r=1e9;
    while(l<r){
        int m=(l+r+1)/2;
        if(chk(m))l=m;
        else r=m-1;
    }
    if(l==0)l=-1;
    cout << l;
}