#include "goatforget.h"
#include <vector>
#include<bits/stdc++.h>

using namespace std;

int N,M,cnt;
bool G[105][105];
int memo[105][105];
vector<int> pos;
vector<int> adj[105];
bool vis[105],used[105];

int jump(int u,int v){
  if(memo[u][v]==-1){
    int x=talk_tae(v);
    talk_tae(u);
    if(x<=v){
      for(int i=x+1;i<=v;++i){
        memo[u][i]=x;
      }
    }else{
      for(int i=v;i<=x-1;++i){
        memo[u][i]=x;
      }
    }
    memo[u][x]=x;
    memo[x][u]=u;
  }
  return memo[u][v];
}

void build(int u,int l,int r){
  if(l>r)return;
  if(cnt==M)return;
  int m=(pos[l]+pos[r]+1)/2;
  int v=jump(u,m);
  int d=abs(v-m);
  int ll=upper_bound(pos.begin(),pos.end(),m-d-1)-pos.begin()-1;
  int rr=lower_bound(pos.begin(),pos.end(),m+d+(v>=m))-pos.begin();
  if(!G[u][v]){
    G[u][v]=G[v][u]=true;
    adj[u].push_back(v);
    adj[v].push_back(u);
    ++cnt;
  }
  if(!used[v]){
    used[v]=true;
    build(u,l,ll);
    build(u,rr,r);
  }else if(v>=m){
    build(u,l,ll);
  }else{
    build(u,rr,r);
  }
}

void sol(int u){
  vis[u]=true;
  for(int i=0;i<N;++i)used[i]=false;
  pos.erase(lower_bound(pos.begin(),pos.end(),u));
  build(u,lower_bound(pos.begin(),pos.end(),jump(u,pos[0]))-pos.begin(),upper_bound(pos.begin(),pos.end(),jump(u,pos[pos.size()-1]))-pos.begin()-1);
  if(cnt==M)return;
  for(int i=adj[u].size()-1;i>=0;--i){
    int v=adj[u][i];
    if(vis[v])continue;
    talk_tae(v);
    sol(v);
    if(cnt==M)return;
    talk_tae(u);
  }
}

std::vector<std::vector<int> > recover_map(int n, int m, int Q){
  // edit this function
  std::vector<std::vector<int> > ans;
  N=n;
  M=m;
  for(int i=0;i<n;++i){
    G[i][i]=true;
    pos.emplace_back(i);
  }
  for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
      memo[i][j]=-1;
    }
  }
  sol(0);
  for(int i=0;i<n;++i){
    for(int j=i+1;j<n;++j){
      if(G[i][j]){
        ans.push_back({i,j});
      }
    }
  }
  return ans;
}
