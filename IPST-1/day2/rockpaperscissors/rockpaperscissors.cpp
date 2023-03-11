#include "rockpaperscissors.h"
#include<bits/stdc++.h>

using namespace std;

int find_cheater1(int N){
	vector<int>notcheat={0};
	int l=1,r=3*N;
	while(l<r){
		int m=(l+r)/2;
		vector<int> res;
		for(int i=l;i<=m;i++)res.push_back(i);
		for(auto i:notcheat)res.push_back(i);
		int tmp=tournament(res);
		if(tmp==res.size()-1){
			for(int i=m+1;i<=r;i++)notcheat.push_back(i);
			r=m;
		}else{
			for(int i=l;i<=m;i++)notcheat.push_back(i);
			l=m+1;
		}
	}
	return l;
}

int find_cheater2(int N){
	bool cant[1005]={};
	int a=3*N-1,b=3*N;
	int ret=tournament({0,a,b});
	if(ret!=2)cant[a]=cant[b]=true;
	while(ret!=1){
		a--,b--;
		if(b<1)b=3*N;
		if(a<1)a=3*N;
		ret=tournament({0,a,b});
		if(ret!=2)cant[a]=cant[b]=true;
	}
	for(int i=3*N;i>0;i--){
		if(i==a||i==b||cant[i])continue;
		ret=tournament({0,a,b,i});
		if(ret==3)return i;
	}
	assert(false);
}
