#include "seats.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1e6+5;
const int K=(1<<21)+5;
const int inf=1e9;

int h,w,n;
int r[N],c[N];
int val[N];
int pref[N];
int tmp[N];

int calc(int x){
	int res=0;
	res+=val[x]>val[x-1]?-1:1;
	res+=val[x]>val[x+1]?-1:1;
	return res;
}

struct segtree{
	struct node{
		int val,freq;
		node():val(inf),freq(0){}
		node(int val,int freq=1):val(val),freq(freq){}
		friend node operator+(node a,node b){
			if(a.val<b.val)return a;
			if(b.val<a.val)return b;
			return node(a.val,a.freq+b.freq);
		}
	}t[K];
	int lz[K];
	void pushlz(int l,int r,int i){
		t[i].val+=lz[i];
		if(l<r){
			lz[i*2]+=lz[i];
			lz[i*2+1]+=lz[i];
		}
		lz[i]=0;
	}
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=node(pref[l]));
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=t[i*2]+t[i*2+1];
	}
	void build(){
		build(1,n,1);
	}
	void update(int l,int r,int i,int x,int y,int v){
		pushlz(l,r,i);
		if(y<l||r<x)return;
		if(x<=l&&r<=y)return lz[i]=v,pushlz(l,r,i),void();
		int m=(l+r)/2;
		update(l,m,i*2,x,y,v);
		update(m+1,r,i*2+1,x,y,v);
		t[i]=t[i*2]+t[i*2+1];
	}
	void update(int x,int y,int v){
		update(1,n,1,x,y,v);
	}
	int query(int l,int r,int i,int x){
		pushlz(l,r,i);
		if(l==r)return t[i].val;
		int m=(l+r)/2;
		if(x<=m)return query(l,m,i*2,x);
		return query(m+1,r,i*2+1,x);
	}
	int query(int x){
		return query(1,n,1,x);
	}
}s;

void give_initial_chart(int H, int W, vector<int> R, vector<int> C){
	h=H,w=W;
	n=h*w;
	val[0]=val[n+1]=n+1;
	for(int i=1;i<=n;i++){
		r[i]=R[i-1]+1;
		c[i]=C[i-1]+1;
		val[c[i]]=i;
	}
	for(int i=1;i<=n;i++){
		pref[i]=pref[i-1]+calc(c[i]);
	}
	s.build();
}

int swap_seats(int a, int b){
	a++,b++;
	if(c[a]>c[b])swap(a,b);
	for(int i=-1;i<=1;i++){
		tmp[val[c[a]+i]]=calc(c[a]+i);
		tmp[val[c[b]+i]]=calc(c[b]+i);
	}
	swap(r[a],r[b]);
	swap(c[a],c[b]);
	val[c[a]]=a;
	val[c[b]]=b;
	for(int i=-1;i<=1;i++){
		if(tmp[val[c[a]+i]]!=inf){
			s.update(val[c[a]+i],n,calc(c[a]+i)-tmp[val[c[a]+i]]);
			tmp[val[c[a]+i]]=inf;
		}
		if(tmp[val[c[b]+i]]!=inf){
			s.update(val[c[b]+i],n,calc(c[b]+i)-tmp[val[c[b]+i]]);
			tmp[val[c[b]+i]]=inf;
		}
	}
	return s.t[1].freq;
}