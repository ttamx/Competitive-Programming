#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,p;
    cin >> n >> m >> p;
    vector<long long> w(n+1);
    for(int i=1;i<=n;i++)cin >> w[i];
    vector<tuple<int,int,long long>> edge;
    vector<vector<long long>> dist(n+1,vector<long long>(n+1,2e9));
    for(int i=1;i<=n;i++)dist[i][i]=0;
    for(int i=0;i<m;i++){
        int u,v;
        long long s;
        cin >> u >> v >> s;
        dist[u][v]=min(dist[u][v],s);
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j||dist[i][j]==2e9)continue;
            edge.emplace_back(i,j,dist[i][j]);
        }
    }
    vector<pair<long long,long long>> dp(n+1,{2e9,0});
    dp[1]={0,p};
    for(int i=1;i<n;i++){
        for(auto [u,v,s]:edge){
            long long val=ceil(1.0*(s-dp[u].second)/w[u]);
            if(val+dp[u].first<dp[v].first){
                dp[v]={val+dp[u].first,dp[u].second+val*w[u]-s};
            }else if(val+dp[u].first==dp[v].first){
                dp[v].second=max(dp[v].second,dp[u].second+val*w[u]-s);
            }
        }
    }
    long long ans=dp[n].first;
    if(ans==2e9)ans=-1;
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}