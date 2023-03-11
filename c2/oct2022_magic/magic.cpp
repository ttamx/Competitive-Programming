#include "magic.h"
#include <bits/stdc++.h>

using namespace std;

vector<int> magic(int N, int M,int Q, vector<int>U, vector<int> V, vector<vector<int>> q){
    vector<int> ans,w(M);
    vector<vector<pair<int,int>>> adj(N);
    for(auto v:q)if(v[0]==0)w[v[1]]=1;
    for(int i=0;i<M;i++)adj[V[i]].push_back({U[i],i});
    vector<int> dp(N,11);
    function<void(int)> dfs=[&](int u){
        for(auto [v,i]:adj[u]){
            if(dp[u]+w[i]>=dp[v])continue;
            dp[v]=dp[u]+w[i];
            dfs(v);
        }
    };
    dp[0]=0;
    dfs(0);
    reverse(q.begin(),q.end());
    for(auto v:q){
        if(v[0]==0){
            w[v[1]]=0;
            ans.push_back(-1);
            if(dp[U[v[1]]]<=dp[V[v[1]]])continue;
            dp[U[v[1]]]=dp[V[v[1]]];
            dfs(U[v[1]]);
        }else{
            ans.push_back(dp[v[1]]<=v[2]);
        }
    }
    reverse(ans.begin(),ans.end());
    return ans;
}