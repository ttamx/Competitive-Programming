#include "wall.h"
#include<bits/stdc++.h>

using namespace std;

const int K=1<<22;
const int INF=INT_MAX/2;

struct segtree{
	int t[K],mn[K],mx[K];
	void apply(int i,int mnn,int mxx){
		t[i]=max(min(t[i],mnn),mxx);
		mn[i]=max(min(mn[i],mnn),mxx);
		mx[i]=max(min(mx[i],mnn),mxx);
	}
	void push(int i){
		apply(i*2,mn[i],mx[i]);
		apply(i*2+1,mn[i],mx[i]);
		mn[i]=INF,mx[i]=-INF;
	}
	void build(int l,int r,int i){
		mn[i]=INF,mx[i]=-INF;
		if(l==r)return;
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
	}
	void update(int l,int r,int i,int x,int y,int mnn,int mxx){
		if(y<l||r<x)return;
		if(x<=l&&r<=y)return apply(i,mnn,mxx);
		int m=(l+r)/2;
		push(i);
		update(l,m,i*2,x,y,mnn,mxx);
		update(m+1,r,i*2+1,x,y,mnn,mxx);
	}
	void answer(int l,int r,int i,int a[]){
		if(l==r)return void(a[l]=t[i]);
		int m=(l+r)/2;
		push(i);
		answer(l,m,i*2,a);
		answer(m+1,r,i*2+1,a);
	}
}s;

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	s.build(0,n-1,1);
	for(int i=0;i<k;i++)s.update(0,n-1,1,left[i],right[i],op[i]==2?height[i]:INF,op[i]==1?height[i]:-INF);
	s.answer(0,n-1,1,finalHeight);
}