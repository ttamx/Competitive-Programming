#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<ll>> dp(n+1,vector<ll>(n+1,1e18));
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        dp[u][v]=dp[v][u]=w;
    }
    for(int i=1;i<=n;i++)dp[i][i]=0;
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
            }
        }
    }
    if(dp[1][n]==1e18)return void(cout << "inf\n");
    vector<pair<string,ll>> ans;
    vector<ll> vec;
    for(int i=1;i<=n;i++)vec.emplace_back(dp[1][i]);
    ll sum=0;
    sort(vec.begin(),vec.end());
    for(int i=1;i<vec.size();i++){
        if(vec[i]>dp[1][n])break;
        ll res=vec[i]-vec[i-1];
        if(res==0)continue;
        string s="";
        for(int j=1;j<=n;j++)s.push_back(dp[1][j]<vec[i]?'1':'0');
        ans.emplace_back(s,res);
        sum+=res;
    }
    cout << sum << " " << ans.size() << "\n";
    for(auto [x,y]:ans)cout << x << " " << y << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}