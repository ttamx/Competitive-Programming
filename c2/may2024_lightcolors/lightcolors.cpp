#include"lightcolors.h"
#include<bits/stdc++.h>

using namespace std;

vector<int> lightcolors(int N,int M,vector<int> A,vector<int> B){
	vector<vector<int>> adj(N);
	for(int i=0;i<M;i++){
		adj[A[i]].emplace_back(B[i]);
		adj[B[i]].emplace_back(A[i]);
	}
	vector<vector<bool>> ok(N,vector<bool>(3,true));
	vector<int> cnt(N,3),col(N);
	using P = pair<int,int>;
	priority_queue<P,vector<P>,greater<P>> pq;
	for(int i=0;i<N;i++)pq.emplace(3,i);
	while(!pq.empty()){
		auto [d,u]=pq.top();
		pq.pop();
		if(col[u])continue;
		for(int i=0;i<3;i++)if(ok[u][i]){
			col[u]=i+1;
			break;
		}
		for(auto v:adj[u])if(ok[v][col[u]-1]){
			ok[v][col[u]-1]=false;
			pq.emplace(--cnt[v],v);
		}
	}
	return col;
}
