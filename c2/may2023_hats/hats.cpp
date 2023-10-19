#include "hats.h"
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> a={
	{0,0,0,0,0,0,1},
	{0,0,0,0,1,1,0},
	{0,0,1,1,0,0,0},
	{1,1,0,0,0,0,0},
	{0,1,0,1,1,0,0},
	{0,1,1,0,0,1,0},
	{1,0,0,1,0,1,0},
	{1,0,1,0,1,0,0},
	{1,1,1,1,1,1,0},
	{1,1,1,1,0,0,1},
	{1,1,0,0,1,1,1},
	{0,0,1,1,1,1,1},
	{1,0,1,0,0,1,1},
	{1,0,0,1,1,0,1},
	{0,1,1,0,1,0,1},
	{0,1,0,1,0,1,1}
};

int count(vector<int> a,vector<int> b){
	int res=0;
	for(int i=0;i<a.size();i++)res+=a[i]==b[i];
	return res;
}

int think(int N, int id, vector<int> hats) {
	if(N==3){
		int cnt[2]={};
		for(auto x:hats)if(x!=-1)cnt[x]++;
		if(cnt[0]==2)return 1;
		if(cnt[1]==2)return 0;
		return -1;
	}
	for(auto v:a)if(count(hats,v)==6)return v[id]^1;
	return -1;
}