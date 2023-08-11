#include "seats.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1e6+5;
const int K=(1<<21)+5;
const int inf=1e9;

int h,w,n;
int R[N],C[N];

struct segtree{
	struct node{
		int mnr,mxr,mnc,mxc;
		node():mnr(inf),mxr(-inf),mnc(inf),mxc(-inf){}
		node(int r,int c):mnr(r),mxr(r),mnc(c),mxc(c){}
		friend node operator+(node a,node b){
			node c;
			c.mnr=min(a.mnr,b.mnr);
			c.mxr=max(a.mxr,b.mxr);
			c.mnc=min(a.mnc,b.mnc);
			c.mxc=max(a.mxc,b.mxc);
			return c;
		}
		int calc(){
			return (mxr-mnr+1)*(mxc-mnc+1);
		}
	}t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=node(R[l],C[l]));
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=t[i*2]+t[i*2+1];
	}
	void build(){
		build(1,n,1);
	}
	void update(int l,int r,int i,int x){
		if(x<l||r<x)return;
		if(l==r)return void(t[i]=node(R[l],C[l]));
		int m=(l+r)/2;
		update(l,m,i*2,x);
		update(m+1,r,i*2+1,x);
		t[i]=t[i*2]+t[i*2+1];
	}
	void update(int x){
		update(1,n,1,x);
	}
	node query(int l,int r,int i,int x,int y){
		if(y<l||r<x)return node();
		if(x<=l&&r<=y)return t[i];
		int m=(l+r)/2;
		return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
	}
	node query(int x,int y){
		return query(1,n,1,x,y);
	}
}s;

void give_initial_chart(int H, int W, vector<int> _R, vector<int> _C){
	h=H,w=W;
	n=h*w;
	for(int i=1;i<=n;i++){
		R[i]=_R[i-1];
		C[i]=_C[i-1];
	}
	s.build();
}

int swap_seats(int a, int b){
	a++,b++;
	swap(R[a],R[b]);
	swap(C[a],C[b]);
	s.update(a);
	s.update(b);
	int idx=1,ans=0;
	while(idx<=n){
		int sz=s.query(1,idx).calc();
		if(sz==idx){
			ans++;
			idx++;
		}else{
			idx=sz;
		}
	}
	return ans;
}