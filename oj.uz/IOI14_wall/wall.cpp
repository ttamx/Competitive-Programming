#include "wall.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int K=1<<22;
const ll inf=1e18;

int n;

struct segtree{
	ll ta[K],td[K];
	void build(int l,int r,int i){
		ta[i]=0;
		td[i]=inf;
		if(l==r)return;
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
	}
	void build(){
		build(0,n-1,1);
	}
	void add(int l,int r,int i,int x,int y,ll v){
		if(y<l||r<x)return;
		v=max(v,ta[i]);
		v=min(v,td[i]);
		if(x<=l&&r<=y)return void(ta[i]=v);
		int m=(l+r)/2;
		add(l,m,i*2,x,y,v);
		add(m+1,r,i*2+1,x,y,v);
	}
	void add(int x,int y,ll v){
		add(0,n-1,1,x,y,v);
	}
	void del(int l,int r,int i,int x,int y,ll v){
		if(y<l||r<x)return;
		v=max(v,ta[i]);
		v=min(v,td[i]);
		if(x<=l&&r<=y)return void(td[i]=v);
		int m=(l+r)/2;
		del(l,m,i*2,x,y,v);
		del(m+1,r,i*2+1,x,y,v);;
	}
	void del(int x,int y,ll v){
		del(0,n-1,1,x,y,v);
	}
	ll query(int l,int r,int i,int x,ll v){
		v=max(v,ta[i]);
		v=min(v,td[i]);
		if(l==r)return v;
		int m=(l+r)/2;
		if(x<=m)return query(l,m,i*2,x,v);
		return query(m+1,r,i*2+1,x,v);
	}
	ll query(int x){
		return query(0,n-1,1,x,0);
	}
}s;

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	::n=n;
	s.build();
	for(int i=k-1;i>=0;i--){
		if(op[i]==1)s.add(left[i],right[i],height[i]);
		else s.del(left[i],right[i],height[i]);
	}
	for(int i=0;i<n;i++)finalHeight[i]=s.query(i);
}