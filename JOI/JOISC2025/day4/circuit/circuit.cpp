#include "circuit.h"
#include <bits/stdc++.h>

using namespace std;

string solve(int N,int R,vector<int> A,vector<int> B){
	string ans(N,'&');
	string tmp(2*N+1,'0');
	function<void(int,char)> dfs_fill=[&](int u,char v){
		if(u>=N){
			tmp[u]=v;
			return;
		}
		dfs_fill(A[u],v);
		dfs_fill(B[u],v);
	};
	function<void(int)> dfs=[&](int u){
		if(u>=N)return;
		dfs_fill(A[u],'0');
		dfs_fill(B[u],'1');
		int val=query(tmp);
		dfs_fill(B[u],'0');
		if(val){
			ans[u]='|';
			dfs(A[u]);
			dfs(B[u]);
		}else{
			dfs_fill(B[u],'1');
			dfs(A[u]);
			dfs_fill(B[u],'0');
			dfs_fill(A[u],'1');
			dfs(B[u]);
			dfs_fill(A[u],'0');
		}
	};
	dfs(0);
	return ans;
}
