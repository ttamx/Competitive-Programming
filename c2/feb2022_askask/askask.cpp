#include "askask.h"
#include <vector>
#include<bits/stdc++.h>

using namespace std;

bool getbit(int x,int y){
  return (x&(1<<y))>>y;
}

std::vector<int> find_bombs(int n){
  vector<vector<int>> z;
  n--;
  for(int i=0;i<64;i++){
    vector<int> tmp;
    z.push_back(tmp);
  }
  int idx;
  for(int i=0;i<=n;++i){
    idx=0;
    for(int j=0;j<6;++j){
      for(int k=j+1;k<6;++k){
        if(getbit(i,j)&&!getbit(i,k))z[idx].push_back(i);
        idx++;
      }
    }
    for(int j=0;j<6;++j){
      for(int k=j+1;k<6;++k){
        if(!getbit(i,j)&&getbit(i,k))z[idx].push_back(i);
        idx++;
      }
    }
  }
  vector<int> ans;
  vector<bool> res=analyse(z);
  for(int i=0;i<=n;++i){
    bool tmp=true;
    idx=0;
    for(int j=0;j<6;++j){
      for(int k=j+1;k<6;++k){
        if(getbit(i,j)&&!getbit(i,k))tmp&=res[idx];
        idx++;
      }
    }
    for(int j=0;j<6;++j){
      for(int k=j+1;k<6;++k){
        if(!getbit(i,j)&&getbit(i,k))tmp&=res[idx];
        idx++;
      }
    }
    if(tmp){
      ans.emplace_back(i);
    }
  }
  if(ans.size()==2)return ans;
  return {ans[0], ans[0]};
}