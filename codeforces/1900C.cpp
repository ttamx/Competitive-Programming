#include<bits/stdc++.h>

using namespace std;

const int inf=1e9;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    s=" "+s;
    vector<int> l(n+2),r(n+2),dp(n+2,inf);
    for(int i=1;i<=n;i++)cin >> l[i] >> r[i];
    function<void(int)> dfs=[&](int u){
        if(l[u]==0&&r[u]==0)dp[u]=0;
        if(l[u]){
            dfs(l[u]);
            if(s[u]=='L')dp[u]=min(dp[u],dp[l[u]]);
            else dp[u]=min(dp[u],dp[l[u]]+1);
        }
        if(r[u]){
            dfs(r[u]);
            if(s[u]=='R')dp[u]=min(dp[u],dp[r[u]]);
            else dp[u]=min(dp[u],dp[r[u]]+1);
        }
    };
    dfs(1);
    cout << dp[1] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}