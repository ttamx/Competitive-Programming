#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> dp(2*n+1);
    vector<vector<int>> adj(n);
    int idx=n;
    for(int i=0;i<n;i++){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        if(a){
            dp[idx]=b;
            adj[i].push_back(idx++);
        }else{
            adj[i].push_back(b-1);
        }
        if(c){
            dp[idx]=d;
            adj[i].push_back(idx++);
        }else{
            adj[i].push_back(d-1);
        }
    }
    int ans=0;
    function<void(int)> dfs=[&](int u){
        for(auto v:adj[u])if(v<n)dfs(v);
        int dif=abs(dp[adj[u][0]]-dp[adj[u][1]]);
        ans+=dif;
        dp[u]=dp[adj[u][0]]+dp[adj[u][1]]+dif;
    };
    dfs(0);
    cout << ans;
}