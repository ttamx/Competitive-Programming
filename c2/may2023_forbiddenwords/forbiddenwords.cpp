#include "forbiddenwords.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;
typedef long long ll;

vector<p2> alice(int M, int N, int K, ll X, vector<p2> F){
	vector<p2> words;
	vector<vector<bool>> del(M,vector<bool>(M));
	for(auto [x,y]:F)del[x][y]=del[y][x]=true;
	vector<bool> used(M);
	for(int i=0;i<M;i++)for(int j=0;j<i;j++)for(int k=0;k<j;k++){
		if(del[i][j]||del[j][k]||del[k][i])continue;
		words.emplace_back(i,j);
		words.emplace_back(j,k);
		words.emplace_back(k,i);
		used[i]=used[j]=used[k]=true;
	}
	vector<int> ans;
	vector<vector<ll>> C(M,vector<ll>(M,0));
	for(int i=0;i<M;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	vector<ll> dp(M);
	for(int i=1;i<M;i++)dp[i]=C[52+i-1][i-1];
	return words;
}


ll bob(int M, vector<p2> W){
	return 0;
}

