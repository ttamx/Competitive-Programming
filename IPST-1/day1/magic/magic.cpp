#include "magic.h"
#include <bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m;
int cut[N];
int can[N];
vector<pair<int,int>> adj[N];

void dfs(int u){
	for(auto [v,i]:adj[u]){
		if(cut[i]){
			if(can[u]+1>=can[v])continue;
			can[v]=can[u]+1;
			dfs(v);
		}else{
			if(can[u]>=can[v])continue;
			can[v]=can[u];
			dfs(v);
		}
	}
}

vector<int> magic(int N, int M,int Q, vector<int>U, vector<int> V, vector<vector<int> >q){
  	vector<int>ans;
  	n=N,m=M;
  	for(int i=0;i<n;i++)can[i]=11;
  	for(auto v:q){
  		if(v[0]==0)cut[v[1]]=true;
  	}
  	for(int i=0;i<m;i++){
   		adj[V[i]].push_back({U[i],i});
    }
  	can[0]=0;
  	dfs(0);
  	reverse(q.begin(),q.end());
  	for(auto v:q){
  		if(v[0]==0){
  			cut[v[1]]=false;
  			if(can[V[v[1]]]<can[U[v[1]]]){
          can[U[v[1]]]=can[V[v[1]]];
          dfs(U[v[1]]);
        }
  			ans.push_back(-1);
  		}else{
  			if(can[v[1]]<=v[2])ans.push_back(1);
  			else ans.push_back(0);
  		}
  	}
  	reverse(ans.begin(),ans.end());
  	return ans;
}
