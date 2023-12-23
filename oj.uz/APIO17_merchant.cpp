#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=105;
const int M=205;
const int K=1005;
const ll inf=1e18;

int n,k,m;
ll b[N][K],s[N][K];
ll dist[N][N],prof[N][N],dp[N][N];

void foyld(ll (&d)[N][N]){
    for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}

bool check(ll cost){
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j]=dist[i][j]<inf?dist[i][j]*cost-prof[i][j]:inf;
    foyld(dp);
    for(int i=1;i<=n;i++)if(dp[i][i]<=0)return true;
    return false;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++)for(int j=1;j<=k;j++)cin >> b[i][j] >> s[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dist[i][j]=inf;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        dist[u][v]=w;
    }
    foyld(dist);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)for(int k=1;k<=::k;k++)if(b[i][k]>0&&s[j][k]>0)
            prof[i][j]=max(prof[i][j],s[j][k]-b[i][k]);
    ll l=0,r=1e9;
    while(l<r){
        ll m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    cout << l << "\n";
}