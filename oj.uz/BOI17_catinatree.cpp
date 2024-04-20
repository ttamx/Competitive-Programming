#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,d;
vector<int> adj[N];
deque<int> dp[N];

int get(int i,int j){
    return j<dp[i].size()?dp[i][j]:0;
}

void dfs(int u){
    dp[u].emplace_back(1);
    for(auto v:adj[u]){
        dfs(v);
        dp[v].emplace_front(dp[v][0]);
        if(dp[v].size()>dp[u].size())swap(dp[u],dp[v]);
        for(int i=0;i<dp[v].size();i++){
            int du=dp[u][i]+get(v,max(i,d-i));
            int dv=dp[v][i]+get(u,max(i,d-i));
            dp[u][i]=max(du,dv);
        }
        for(int i=dp[v].size()-2;i>=0;i--)dp[u][i]=max(dp[u][i],dp[u][i+1]);
        dp[v].clear();
    }
    if(dp[u].size()>d)dp[u].pop_back();
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> d;
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    dfs(0);
    cout << dp[0][0];
}