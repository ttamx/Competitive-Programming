#include "worldmap.h"
#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> create_map(int n,int m,vector<int> a,vector<int> b){
  vector<vector<int>> ans(3*n,vector<int>(3*n));
  vector<vector<int>> adj(n+1);
  for(int i=0;i<m;i++){
    adj[a[i]].emplace_back(b[i]);
    adj[b[i]].emplace_back(a[i]);
  }
  vector<int> disc(n+1),sz(n+1);
  int timer=0;
  function<int(int,int,int)> dfs=[&](int u,int d,int st){
    sz[u]=1;
    disc[u]=++timer;
    int cur=st;
    if(u!=1)cur++;
    for(auto v:adj[u])if(!disc[v]){
      cur=dfs(v,d+1,cur)+1;
      sz[u]+=sz[v];
    }
    cur=max(cur,st+2*sz[u]-1);
    for(int i=0;i<3;i++){
      for(int j=st;j<cur;j++){
        ans[d*3+i][j]=u;
      }
    }
    int pos=st+1;
    for(auto v:adj[u])if(disc[v]>disc[u]){
      assert(pos<cur);
      ans[d*3+1][pos]=v;
      pos+=2;
    }
    return cur;
  };
  dfs(1,0,0);
  for(int i=1;i<3*n;i++){
    for(int j=0;j<3*n;j++){
      if(!ans[i][j]){
        ans[i][j]=ans[i-1][j];
      }
    }
  }
  for(int i=0;i<3*n;i++){
    for(int j=1;j<3*n;j++){
      if(!ans[i][j]){
        ans[i][j]=ans[i][j-1];
      }
    }
  }
  return ans;
}
