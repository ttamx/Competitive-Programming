#include "grader.h"
#include "decoder.h"
#include<bits/stdc++.h>

using namespace std;

void decode(int n, int h) {
   vector<int> p(n);
	for(int i=1;i<n;i++)for(int j=0;j<10;j++)p[i]+=decode_bit()<<j;
	vector<vector<pair<int,int>>> adj(n);
	for(int i=1;i<n;i++){
		int u=i,v=p[i];
		adj[u].emplace_back(v,i-1);
		adj[v].emplace_back(u,i-1);
	}
   for(int i=0;i<h;i++){
      vector<int> val(n-1);
		while(val.size()%5!=0)val.emplace_back(0);
      for(int i=0;i<val.size();i+=5){
         int cur=0;
         for(int j=0;j<8;j++)cur+=decode_bit()<<j;
         for(int j=4;j>=0;j--){
            val[i+j]=cur%3-1;
            cur/=3;
         }
      }
      vector<int> dist(n);
      function<void(int,int)> dfs=[&](int u,int p){
         for(auto [v,id]:adj[u]){
            if(v==p)continue;
            dist[v]=dist[u]+val[id];
            dfs(v,u);
         }
      };
      dist[i]=0;
      dfs(i,-1);
      for(int j=0;j<n;j++)hops(i,j,dist[j]);
   }
}