#include "capybara.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,ll> p2;

const int N=2e5+5;
const int K=1<<19;


int n,q;
int a[N],m[N],k[N],lm[N],rm[N];
ll qs[N];

struct maxsegtree{
	int t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=l);
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=max(t[i*2],t[i*2+1]);
	}
	void build(){
		build(1,n,1);
	}
	void update(int l,int r,int i,int x,int v){
		if(x<l||r<x)return;
		if(l==r)return void(t[i]=max(t[i],v));
		int m=(l+r)/2;
		update(l,m,i*2,x,v);
		update(m+1,r,i*2+1,x,v);
		t[i]=max(t[i*2],t[i*2+1]);
	}
	void update(int x,int v){
		update(1,n,1,x,v);
	}
	int query(int l,int r,int i,int x,int y){
		if(y<l||r<x)return -2e9;
		if(x<=l&&r<=y)return t[i];
		int m=(l+r)/2;
		return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
	}
	int query(int x,int y){
		return query(1,n,1,x,y);
	}
}sr;

struct minsegtree{
	int t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=l);
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=min(t[i*2],t[i*2+1]);
	}
	void build(){
		build(1,n,1);
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
		update(1,n,1,x,v);
	}
	int query(int l,int r,int i,int x,int y){
		if(y<l||r<x)return 2e9;
		if(x<=l&&r<=y)return t[i];
		int m=(l+r)/2;
		return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
	}
	int query(int x,int y){
		return query(1,n,1,x,y);
	}
}sl;

int goleft(int i,ll val){
	int l=1,r=i;
	while(l<r){
		int mid=(l+r)/2;
		if(qs[i]-qs[mid]<=val)r=mid;
		else l=mid+1;
	}
	return l;
}

int goright(int i,ll val){
	int l=i,r=n;
	while(l<r){
		int mid=(l+r+1)/2;
		if(qs[mid]-qs[i]<=val)l=mid;
		else r=mid-1;
	}
	return r;
}

pair<int,int> go(int i,ll val){
	int l=goleft(i,val);
	int r=goright(i,val);
	int resl=l+1,resr=r-1;
	while(l<resl||resr<r){
		if(l<1||r>n)break;
		resl=l;
		resr=r;
		r=sr.query(resl,resr);
		l=sl.query(resl,resr);
	}
	return {resl,resr};
}

void capybara(int N, int Q, vector<int> M, vector<int> K){
	n=N,q=Q;
	for(int i=0;i<n;i++){
		m[i+1]=M[i];
		k[i+1]=K[i];
	}
	for(int i=2;i<=n;i++){
		qs[i]=qs[i-1]+k[i-1];
	}
}

long long travel(int a,int b){
	a++,b++;
	return abs(qs[a]-qs[b]);
}