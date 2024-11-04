#include "reach.h"
#include <bits/stdc++.h>

using namespace std;

const int K=1<<19;
const int INF=INT_MAX/2;

struct SegTree{
	int n;
	int t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=l);
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=min(t[i*2],t[i*2+1]);
	}
	void init(int _n){
		n=_n;
		build(0,n-1,1);
	}
	void update(int l,int r,int i,int x,int v){
		if(x<l||r<x)return;
		if(l==r)return void(t[i]=min(t[i],v));
		int m=(l+r)/2;
		update(l,m,i*2,x,v);
		update(m+1,r,i*2+1,x,v);
		t[i]=min(t[i*2],t[i*2+1]);
	}
	void update(int x,int v){
		update(0,n-1,1,x,v);
	}
	int query(int l,int r,int i,int x,int y){
		if(y<l||r<x)return INF;
		if(x<=l&&r<=y)return t[i];
		int m=(l+r)/2;
		return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
	}
	int query(int x,int y){
		return query(0,n-1,1,x,y);
	}
}seg;

void initialize(int n){
	seg.init(n);
}

void add_arc(int u,int v){
	seg.update(v,u);
}

bool is_reachable(int u,int v,int t){
	if(t<u)return true;
	if(t<=v)return false;
	return seg.query(v+1,t)<u;
}