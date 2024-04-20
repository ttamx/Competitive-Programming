#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int K=45;
const int M=(1<<20)+5;
const ll inf=1e18;

int n,m,k,h,h2;
ll c[N],w[N];
bool adj[K][K];
ll dp[M];
ll ans=inf;

void sol(int mask){
    int res=0;
    ll sum=0;
    for(int i=0;i<h;i++){
        if(mask>>i&1){
            sum+=w[i];
            continue;
        }
        for(int j=0;j<h;j++){
            if(!adj[i][j])continue;
            if(mask>>j&1)continue;
            return;
        }
        for(int j=h;j<k;j++){
            if(!adj[i][j])continue;
            res|=1<<(j-h);
        }
    }
    dp[res]=min(dp[res],sum);
}

void sol2(int mask){
    ll sum=dp[mask];
    for(int i=0;i<h2;i++){
        if(mask>>i&1){
            sum+=w[i+h];
            continue;
        }
        for(int j=0;j<h2;j++){
            if(!adj[i+h][j+h])continue;
            if(mask>>j&1)continue;
            return;
        }
    }
    ans=min(ans,sum);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++)cin >> c[i],c[i]--;
    for(int i=0;i<n;i++)cin >> w[i];
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        u=c[u],v=c[v];
        adj[u][v]=adj[v][u]=1;
    }
    adj[c[1]][c[1]]=1;
    h=k/2;
    h2=k-h;
    for(int i=0;i<1<<h2;i++)dp[i]=inf;
    for(int i=0;i<1<<h;i++)sol(i);
    for(int i=0;i<1<<h2;i++){
        for(int j=0;j<h2;j++){
            if(i>>j&1){
                dp[i]=min(dp[i],dp[i^(1<<j)]);
            }
        }
    }
    for(int i=0;i<1<<h2;i++)sol2(i);
    cout << ans << "\n";
}