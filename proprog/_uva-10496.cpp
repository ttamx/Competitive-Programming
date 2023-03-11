#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,h,w,sx,sy;
    cin >> h >> w >> sx >> sy >> n;
    vector<pair<int,int>> a(n+1);
    a[0]={sx,sy};
    for(int i=1;i<=n;i++)cin >> a[i].first >> a[i].second;
    vector<vector<int>> dp(n+1,vector<int>(2<<n,1e9));
    dp[0][0]=0;
    for(int i=0;i<2<<n;i++){
        for(int u=0;u<=n;u++){
            for(int v=0;v<=n;v++){
                dp[v][i|(1<<v)]=min(dp[v][i|(1<<v)],dp[u][i]+abs(a[u].first-a[v].first)+abs(a[u].second-a[v].second));
            }
        }
    }
    cout << "The shortest path has length " << dp[0][(2<<n)-1] << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}