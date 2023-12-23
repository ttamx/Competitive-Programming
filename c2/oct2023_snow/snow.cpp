#include "snow.h"
#include <bits/stdc++.h>

using namespace std;

vector<int> find_pair(int N, int M, vector<int>U, vector<int> V){
    vector<int> ans;
    vector<vector<pair<int,int>>> adj(N);
    for(int i=0;i<M;i++){
        int u=U[i],v=V[i];
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    auto solve=[&](int rt){
        vector<pair<int,int>> q;
        vector<bool> vis(N);
        q.emplace_back(rt,-1);
        vis[rt]=true;
        for(int i=0;i<N;i++){
            int u=q[i].first;
            for(auto [v,id]:adj[u])if(!vis[v]){
                q.emplace_back(v,id);
                vis[v]=true;
            }
        }
        int l=0,r=N-1;
        while(l<r){
            int m=(l+r)/2;
            vector<bool> res(M);
            for(int i=1;i<=m;i++)res[q[i].second]=true;
            if(road_salt(res))r=m;
            else l=m+1;
        }
        ans.emplace_back(q[l].first);
        return q[l].first;
    };
    solve(solve(0));
    return ans;
}