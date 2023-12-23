#include "rockpaperscissors.h"
#include<bits/stdc++.h>

using namespace std;

int find_cheater1(int n){
	vector<int> v;
	v.emplace_back(0);
	int l=1,r=3*n;
	while(l<r){
		int mid=(l+r)/2;
		vector<int>res=v;
		for(int i=l;i<=mid;i++)res.emplace_back(i);
		if(tournament(res)==res.size()-1){
			for(int i=mid+1;i<=r;i++)v.emplace_back(i);
			r=mid;
		}else{
			for(int i=l;i<=mid;i++)v.emplace_back(i);
			l=mid+1;
		}
	}
	return l;
}

int find_cheater2(int n){
	vector<int> res;
	for(int i=2;i<=3*n;i++)if(tournament({0,1,i})==2)res.emplace_back(i);
	if(res.size()==3*n-1)return 1;
	int id=0;
	vector<int> res2,res3;
	for(bool ok=false;id+2<res.size();id+=3){
		vector<int> tmp;
		for(int i=0;i<3;i++)tmp.emplace_back(res[id+i]);
		if(ok){
			for(auto x:tmp)res3.emplace_back(x);
		}else if(tournament(tmp)==2){
			res2=tmp;
			ok=true;
		}else{
			for(auto x:tmp)res3.emplace_back(x);
		}
	}
	if(res2.empty())for(;id<res.size();id++)res2.emplace_back(res[id]);
	vector<bool> ok(3*n+2);
	for(auto x:res2)ok[x]=true;
	if(res3.size()<2){
		for(auto x:res2){
			vector<int> tmp;
			for(int i=0;i<=3*n;i++)if(i==x||!ok[i])tmp.emplace_back(i);
			if(tournament(tmp)==tmp.size()-1)return x;
		}
	}else{
		for(auto x:res2){
			if(tournament({res3[0],res3[1],x})==2)return x;
		}
	}
	return 1;
}
