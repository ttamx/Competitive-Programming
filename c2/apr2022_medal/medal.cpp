#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n,q;
int w[N],lv[N],pa[N][20];
ll dp[N][20][15],sum[N][20];
vector<int> adj[N];

void dfs(int u,int p){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    sum[u][0]=w[u];
    for(auto v:adj[u])if(v!=p)dfs(v,u);
}

void initialize(int N,int Q,vector<int> W,vector<pair<int,int>> R){
    n=N,q=Q;
    for(int i=1;i<=n;i++)w[i]=W[i-1];
    for(auto [u,v]:R){
        u++,v++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    for(int l=1;l<=10;l++)for(int u=1;u<=n;u++)for(auto v:adj[u])dp[u][0][l]=max(dp[u][0][l],w[u]+w[v]+dp[v][0][l-1]);
    for(int i=1;i<20;i++)for(int j=1;j<=n;j++){
        pa[j][i]=pa[pa[j][i-1]][i-1];
        sum[j][i]=sum[pa[j][i-1]][i-1]+sum[j][i-1];
        for(int k=1;k<=10;k++)dp[j][i][k]=max(dp[j][i-1][k],dp[pa[j][i-1]][i-1][k]);
    }
    return;
}

ll query(int a,int b,int x){
    a++,b++;
    x/=2;
    if(lv[a]<lv[b])swap(a,b);
    ll all=0;
    ll mx[15]={};
    for(int i=19;i>=0;i--){
        if(lv[pa[a][i]]>=lv[b]){
            for(int j=1;j<=x;j++)mx[j]=max(mx[j],dp[a][i][j]);
            all+=sum[a][i];
            a=pa[a][i];
        }
    }
    if(a!=b){
        for(int i=19;i>=0;i--){
            if(pa[a][i]!=pa[b][i]){
                for(int j=1;j<=x;j++)mx[j]=max({mx[j],dp[a][i][j],dp[b][i][j]});
                all+=sum[a][i]+sum[b][i];
                a=pa[a][i];
                b=pa[b][i];
            }
        }
        for(int j=1;j<=x;j++)mx[j]=max({mx[j],dp[a][0][j],dp[b][0][j]});
        all+=w[a]+w[b];
        a=pa[a][0];
    }
    for(int j=1;j<=x;j++)mx[j]=max(mx[j],dp[a][0][j]);
    all+=w[a];
    for(int i=2;i<=x;i++)for(int j=1;j<i;j++)mx[i]=max(mx[i],mx[j]+mx[i-j]);
    return all+mx[x];
}
