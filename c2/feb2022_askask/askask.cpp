#include "askask.h"
#include<bits/stdc++.h>

using namespace std;

vector<int> find_bombs(int N){
	vector<vector<int>> Z;
	if(N!=64){
		for(int b=0;(1<<b)<N;b++){
			vector<int> z;
			for(int i=0;i<N;i++)if(i>>b&1)z.emplace_back(i);
			Z.emplace_back(z);
		}
		auto res=analyse(Z);
		int ans=0;
		for(int i=0;i<res.size();i++)if(res[i])ans|=1<<i;
		return {ans,ans};
	}
	for(int i=0;i<8;i++){
		vector<int> z;
		for(int j=0;j<8;j++)z.emplace_back(i<<3|j);
		Z.emplace_back(z);
	}
	for(int i=0;i<8;i++){
		vector<int> z;
		for(int j=0;j<8;j++)z.emplace_back(j<<3|i);
		Z.emplace_back(z);
	}
	vector<int> gp(N);
	Z.resize(23);
	for(int i=0;i<8;i++)for(int j=0;j<8;j++){
		int g=gp[i<<3|j]=abs(i-j);
		if(g<7)Z[16+g].emplace_back(i<<3|j);
	}
	auto res=analyse(Z);
	vector<int> X,Y;
	for(int i=0;i<8;i++)if(res[i])X.emplace_back(i);
	for(int i=0;i<8;i++)if(res[i+8])Y.emplace_back(i);
	vector<int> pt;
	for(auto x:X)for(auto y:Y)pt.emplace_back(x<<3|y);
	if(pt.size()==1)return {pt[0],pt[0]};
	if(pt.size()==2)return pt;
	int cnt=0;
	vector<int> ok(7);
	for(int i=16;i<23;i++)cnt+=(ok[i-16]=res[i]);
	if(cnt==0)return {7,56};
	if(cnt==1)for(int i=0;i<2;i++)if(ok[gp[pt[i]]]&&ok[gp[pt[3-i]]])return {pt[i],pt[3-i]};
	if(cnt==2)for(int i=0;i<2;i++)if(gp[pt[i]]!=gp[pt[3-i]]&&ok[gp[pt[i]]]&&ok[gp[pt[3-i]]])return {pt[i],pt[3-i]};
	return {-1,-1};
}