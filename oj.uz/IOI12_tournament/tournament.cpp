#include<bits/stdc++.h>
#include "grader.cpp"

using namespace std;

const int K=1<<18;

struct segtree{
	pair<int,int> t[K];
	bool lz[K];
	void pushlz(int l,int r,int i){
		if(!lz[i])return;
		t[i]={2e9,2e9};
		if(l<r){
			lz[i*2]=lz[i*2+1]=true;
		}
		lz[i]=false;
	}
	void build(int l,int r,int i,int *a){
		if(l==r)return void(t[i]={-a[l],l});
		int m=(l+r)/2;
		build(l,m,i*2,a);
		build(m+1,r,i*2+1,a);
		t[i]=min(t[i*2],t[i*2+1]);
	}
	void update(int l,int r,int i,int x,pair<int,int> v){
		pushlz(l,r,i);
		if(x<l||r<x)return;
		if(l==r)return void(t[i]=v);
		int m=(l+r)/2;
		update(l,m,i*2,x,v);
		update(m+1,r,i*2+1,x,v);
		t[i]=min(t[i*2],t[i*2+1]);
	}
	void del(int l,int r,int i,int x,int y){
		pushlz(l,r,i);
		if(y<l||r<x)return;
		if(x<=l&&r<=y){
			lz[i]=true;
			pushlz(l,r,i);
			return;
		}
		int m=(l+r)/2;
		del(l,m,i*2,x,y);
		del(m+1,r,i*2+1,x,y);
		t[i]=min(t[i*2],t[i*2+1]);
	}
	pair<int,int> query(int l,int r,int i,int x,int y){
		pushlz(l,r,i);
		if(y<l||r<x)return {2e9,2e9};
		if(x<=l&&r<=y)return t[i];
		int m=(l+r)/2;
		return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
	}
}s;

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E) {
	s.build(0,N-1,1,K);
	for(int i=0;i<C;i++){
		auto [x,y]=s.query(0,N-1,1,S[i],E[i]);
		s.del(0,N-1,1,S[i],E[i]);
		s.update(0,N-1,1,y,{x,y});
	}
	return s.query(0,N-1,1,0,N-1).second;
}
