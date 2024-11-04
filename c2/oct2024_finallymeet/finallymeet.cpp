#include "finallymeet.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll count_init(int n,int m,vector<int> _u,vector<int> _v){
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u=_u[i],v=_v[i];
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> col(n,-1);
    int cnt[2]={};
    bool flag=true;
    ll ans=0;
    function<void(int)> dfs=[&](int u){
        cnt[col[u]]++;
        for(auto v:adj[u]){
            if(col[v]==-1){
                col[v]=col[u]^1;
                dfs(v);
            }else if(col[u]==col[v]){
                flag=false;
            }
        }
    };
    for(int i=0;i<n;i++){
        if(col[i]==-1){
            cnt[0]=cnt[1]=0;
            flag=true;
            col[i]=0;
            dfs(i);
            ans+=1LL*cnt[0]*cnt[0];
            ans+=1LL*cnt[1]*cnt[1];
            if(!flag){
                ans+=2LL*cnt[0]*cnt[1];
            }
        }
    }
    return ans;
}