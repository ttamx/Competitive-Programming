#include "prize.h"
#include<bits/stdc++.h>
 
using namespace std;
 
mt19937 rng(time(nullptr));
 
const int N=2e5+5;
 
int cnt=0;
int n;
int ans=-1;
vector<vector<int>> mem(N);
int mx;
 
vector<int> ask2(int x){
	if(x<0||x>=n)return {0,0};
	if(mem[x].empty()){
		assert(++cnt<=1e4);
		mem[x]=ask(x);
	}
	return mem[x];
}
 
void bsearch(int l,int r){
	if(l>r)return;
	int m=(l+r)/2;
	if(ask2(m)[0]+ask2(m)[1]==0)ans=m;
	if(l==r)return;
	int ml=m,mr=m;
	while(ml>=l&&ask2(ml)[0]+ask2(ml)[1]<mx){
		if(ask2(ml)[0]+ask2(ml)[1]==0)ans=ml;
		ml--;
	}
	while(mr<=r&&ask2(mr)[0]+ask2(mr)[1]<mx){
		if(ask2(mr)[0]+ask2(mr)[1]==0)ans=mr;
		mr++;
	}
	if(ask2(ml)[0]-ask2(l-1)[0]>0){
		bsearch(l,ml-1);
	}
	if(ask2(mr)[1]-ask2(r+1)[1]>0){
		bsearch(mr+1,r);
	}
}
 
int find_best(int _n) {
	n=_n;
	for(int i=0;i<min(n,100);i++){
		auto res=ask2(i);
		mx=max(mx,res[0]+res[1]);
	}
	bsearch(0,n-1);
	return ans;
}