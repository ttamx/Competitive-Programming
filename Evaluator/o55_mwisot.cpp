#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
int w[N];
int dp[N];
vector<int> adj[N];

int sol(int u,int p){
    if(dp[u])return dp[u];
    if(adj[u].size()==1&&u!=p)return dp[u]=w[u];
    int ret1=0;
    for(auto v:adj[u])if(v!=p)ret1+=sol(v,u);
    int ret2=w[u];
    for(auto v:adj[u])if(v!=p)for(auto w:adj[v])if(w!=u)ret2+=sol(w,v);
    return dp[u]=max(ret1,ret2);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;++i)cin >> w[i];
    for(int i=1;i<n;++i){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    cout << sol(0,0);
}