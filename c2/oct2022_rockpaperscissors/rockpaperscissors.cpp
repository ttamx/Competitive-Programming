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
	vector<int> v;
	vector<int> res;
	res.emplace_back(0);
	for(int i=1;i<=3*n;i+=2){
		if(i+1>3*n){
			if(tournament({0,i,1})==2){
				v.emplace_back(i);
				res.emplace_back(i);
			}
		}else{
			if(tournament({0,i,i+1})==2){
				v.emplace_back(i);
				v.emplace_back(i+1);
			}else{
				res.emplace_back(i);
				res.emplace_back(i+1);
			}
		}
	}
	int idx;
	for(idx=3;idx<v.size();idx+=4){
		if(tournament({v[idx-3],v[idx-2],v[idx-1],v[idx]})==3){
			break;
		}
	}
	while(res.size()>n+1)res.pop_back();
	for(int i=idx-3;i<min(idx,(int)v.size()-1);i++){
		res.emplace_back(v[i]);
		if(tournament(res)==res.size()-1)return v[i];
		res.pop_back();
	}
	return v[min(idx,(int)v.size()-1)];
}
