#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/4;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q;
    cin >> n >> m >> q;
    vector<vector<ll>> dp(n,vector<ll>(n,INF));
    vector<tuple<int,int,ll>> edges(m);
    for(auto &[u,v,w]:edges){
        cin >> u >> v >> w;
        u--,v--;
        dp[u][v]=dp[v][u]=min(dp[u][v],w);
    }
    vector<tuple<int,int,ll>> qr(q);
    for(auto &[u,v,w]:qr){
        cin >> u >> v >> w;
        u--,v--;
    }
    for(int i=0;i<n;i++)dp[i][i]=0;
    for(int x=0;x<n;x++)for(int u=0;u<n;u++)for(int v=0;v<n;v++)dp[u][v]=min(dp[u][v],dp[u][x]+dp[x][v]);
    int ans=0;
    for(auto [u,v,w]:edges){
        bool ok=false;
        for(auto [uu,vv,ww]:qr){
            ll d=min(dp[uu][u]+dp[v][vv],dp[uu][v]+dp[u][vv])+w;
            if(d<=ww){
                ok=true;
                break;
            }
        }
        ans+=ok;
    }
    cout << ans << "\n";
}