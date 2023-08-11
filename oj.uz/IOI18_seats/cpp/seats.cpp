#include "seats.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int K=(1<<21)+5;
const int inf=1e9;

int h,w,n;
int r[N],c[N];
vector<vector<int>> val;
int pref[N];
int tmp[N];

int calc(int id){
	if(id==n+1)return inf;
	int x=r[id],y=c[id];
	int res=0;
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			int cnt=1;
			for(int k=0;k<2;k++){
				for(int l=0;l<2;l++){
					if(val[x+i-k][y+j-l]<id)cnt++;
				}
			}
			res+=cnt%2==1?1:-1;
		}
	}
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
	val=vector<vector<int>>(h+2,vector<int>(w+2,n+1));
	for(int i=1;i<=n;i++){
		r[i]=R[i-1]+1;
		c[i]=C[i-1]+1;
		val[r[i]][c[i]]=i;
		tmp[i]=inf;
	}
	for(int i=1;i<=n;i++){
		pref[i]=pref[i-1]+calc(i);
	}
	s.build();
}

int swap_seats(int a, int b){
	a++,b++;
	if(c[a]>c[b])swap(a,b);
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			int id1=val[r[a]+i][c[a]+j];
			int id2=val[r[b]+i][c[b]+j];
			if(tmp[id1]==inf)tmp[id1]=calc(id1);
			if(tmp[id2]==inf)tmp[id2]=calc(id2);
		}
	}
	swap(r[a],r[b]);
	swap(c[a],c[b]);
	val[r[a]][c[a]]=a;
	val[r[b]][c[b]]=b;
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			int id1=val[r[a]+i][c[a]+j];
			int id2=val[r[b]+i][c[b]+j];
			if(tmp[id1]!=inf){
				s.update(id1,n,calc(id1)-tmp[id1]);
				tmp[id1]=inf;
			}
			if(tmp[id2]!=inf){
				s.update(id2,n,calc(id2)-tmp[id2]);
				tmp[id2]=inf;
			}
		}
	}
	return s.t[1].freq;
}