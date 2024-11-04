#include "wall.h"
#include<bits/stdc++.h>

using namespace std;

const int K=1<<22;
const int INF=INT_MAX/2;

int n;

struct segtree{
	int t[K],lzmn[K],lzmx[K];
	void apply(int i,int mn,int mx){
		t[i]=min(t[i],mn);
		t[i]=max(t[i],mx);
		lzmn[i]=min(lzmn[i],mn);
		lzmn[i]=max(lzmn[i],mx);
		lzmx[i]=min(lzmx[i],mn);
		lzmx[i]=max(lzmx[i],mx);
	}
	void push(int i){
		apply(i*2,lzmn[i],lzmx[i]);
		apply(i*2+1,lzmn[i],lzmx[i]);
		lzmn[i]=INF,lzmx[i]=-INF;
	}
	void build(int l,int r,int i){
		t[i]=0,lzmn[i]=INF,lzmx[i]=-INF;
		if(l==r)return;
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
	}
	void build(){
		build(0,n-1,1);
	}
	void update(int l,int r,int i,int x,int y,int mn,int mx){
		if(y<l||r<x)return;
		if(x<=l&&r<=y)return apply(i,mn,mx);
		push(i);
		int m=(l+r)/2;
		update(l,m,i*2,x,y,mn,mx);
		update(m+1,r,i*2+1,x,y,mn,mx);
	}
	void update(int x,int y,int mn,int mx){
		update(0,n-1,1,x,y,mn,mx);
	}
	int query(int l,int r,int i,int x){
		if(l==r)return t[i];
		push(i);
		int m=(l+r)/2;
		if(x<=m)return query(l,m,i*2,x);
		else return query(m+1,r,i*2+1,x);
	}
	int query(int x){
		return query(0,n-1,1,x);
	}
}s;

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	::n=n;
	s.build();
	for(int i=0;i<k;i++){
		s.update(0,n-1,1,left[i],right[i],op[i]==2?height[i]:INF,op[i]==1?height[i]:-INF);
	}
	for(int i=0;i<n;i++){
		finalHeight[i]=s.query(i);
	}
}