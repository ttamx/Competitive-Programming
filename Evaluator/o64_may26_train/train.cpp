#include "train.h"
#include <bits/stdc++.h>

using namespace std;

const int K=1<<19;
const int INF=INT_MAX/2;

struct SegTree{
	int n;
	int t[K],lz[K];
	void build(int l,int r,int i){
		t[i]=lz[i]=INF;
		if(l==r)return;
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
	}
	void init(int _n){
		n=_n;
		build(0,n-1,1);
	}
	void apply(int i,int v){
		t[i]=min(t[i],v);
		lz[i]=min(lz[i],v);
	}
	void push(int i){
		apply(i*2,lz[i]);
		apply(i*2+1,lz[i]);
		lz[i]=INF;
	}
	void update(int l,int r,int i,int x,int y,int v){
		if(y<l||r<x)return;
		if(x<=l&&r<=y)return apply(i,v);
		push(i);
		int m=(l+r)/2;
		update(l,m,i*2,x,y,v);
		update(m+1,r,i*2+1,x,y,v);
		t[i]=min(t[i*2],t[i*2+1]);
	}
	void update(int x,int y,int v){
		update(0,n-1,1,x,y,v);
	}
	int query(int l,int r,int i,int x,int y){
		if(y<l||r<x)return INF;
		if(x<=l&&r<=y)return t[i];
		push(i);
		int m=(l+r)/2;
		return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
	}
	int query(int x,int y){
		return query(0,n-1,1,x,y);
	}
}seg;

int find_min_cost(int n,int m,vector<int>& s,vector<int>& t,vector<int>& c){
	seg.init(n);
	seg.update(0,0,0);
	for(int i=0;i<m;i++){
		int val=seg.query(s[i],t[i]);
		seg.update(s[i],t[i],val+c[i]);
	}
	int ans=seg.query(n-1,n-1);
	return ans<INF?ans:-1;
}
