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

int find_cheater3(int n){
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

int find_cheater2(int n){
	if(n<=100)return find_cheater3(n);
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	vector<int> p(3*n+1);
	iota(p.begin(),p.end(),0);
	shuffle(p.begin()+1,p.end(),rng);
	auto ask=[&](vector<int> a){
		for(auto &x:a)x=p[x];
		return tournament(a);
	};
	vector<int> res;
	for(int i=1;i+1<=3*n;i+=2)if(ask({0,i,i+1})==2)res.emplace_back(i);
	vector<int> res2,res3;
	for(int i=0;i+1<res.size();i+=2){
		if(res2.empty()&&ask({res[i],res[i]+1,res[i+1],res[i+1]+1})==3){
			res2={res[i],res[i+1]};
		}else{
			res3.emplace_back(res[i]);
			res3.emplace_back(res[i+1]);
		}
	}
	if(res2.empty()&&res.size()%2==1&&res.size()>1){
		if(ask({res[0],res[0]+1,res.back(),res.back()+1})==3){
			res2={res.back()};
		}else{
			res3.emplace_back(res.back());
		}
	}
	if(res2.empty()&&n%2==1)res2.emplace_back(3*n);
	if(res.size()==1)res2.emplace_back(res[0]);
	int ans=res2[0];
	for(int i=1;i<4;i+=2)res3.emplace_back(i);
	if(res2.size()>1){
		if(ask({res2[1],res2[1]+1,res3[0],res3[0]+1})==3){
			ans=res2[1];
			res3.emplace_back(res2[0]);
		}else{
			res3.emplace_back(res2[1]);
		}
	}
	if(ans==3*n)return p[ans];
	if(ask({ans,res3[0],res3[0]+1,res3[1],res3[1]+1,0})!=5||ask({ans,res3[0],res3[0]+1,res3[1],res3[1]+1})!=4)ans++;
	return p[ans];
}