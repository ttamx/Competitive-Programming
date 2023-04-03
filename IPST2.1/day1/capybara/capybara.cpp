#pragma optimize O3
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

int lg2[N];
int mn[N][20],mx[N][20];

int rmnq(int l,int r){
	int sz=lg2[r-l+1];
	return min(mn[l][sz],mn[r-(1<<sz)+1][sz]);
}

int rmxq(int l,int r){
	int sz=lg2[r-l+1];
	return max(mx[l][sz],mx[r-(1<<sz)+1][sz]);
}

pair<int,int> gormq(int i,ll val){
	int l=goleft(i,val);
	int r=goright(i,val);
	int resl=l+1,resr=r-1;
	while(l<resl||resr<r){
		if(l<1||r>n)break;
		resl=l;
		resr=r;
		r=rmxq(resl,resr);
		l=rmnq(resl,resr);
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
	sr.build();
	sl.build();
	for(int i=1;i<=n;i++){
		tie(lm[i],rm[i])=go(i,m[i]);
		sl.update(i,lm[i]);
		sr.update(i,rm[i]);
	}
	for(int i=n;i>=1;i--){
		tie(lm[i],rm[i])=go(i,m[i]);
		sl.update(i,lm[i]);
		sr.update(i,rm[i]);
	}
	for(int i=2;i<=n;i++)lg2[i]=lg2[i/2]+1;
	for(int i=1;i<=n;i++)mn[i][0]=sl.query(i,i);
	for(int i=1;i<=n;i++)mx[i][0]=sr.query(i,i);
	for(int i=1;i<20;i++)for(int j=1;j<=n-(1<<i)+1;j++)mn[j][i]=min(mn[j][i-1],mn[j+(1<<(i-1))][i-1]);
	for(int i=1;i<20;i++)for(int j=1;j<=n-(1<<i)+1;j++)mx[j][i]=max(mx[j][i-1],mx[j+(1<<(i-1))][i-1]);
}

mt19937 rng(time(0));

long long travel(int a,int b){
	a++,b++;
	if(a==b||(lm[a]<=b&&b<=rm[a]))return m[a];
	int l=a+1,r=n+1;
	while(l<r){
		int mid=(l+r)/2;
		auto [ql,qr]=gormq(a,qs[mid]-qs[a]);
		if(ql<=b&&b<=qr)r=mid;
		else l=mid+1;
	}
	ll res=1e18;
	if(r<=n)res=min(res,qs[l]-qs[a]);
	l=0,r=a-1;
	while(l<r){
		int mid=(l+r+1)/2;
		auto [ql,qr]=gormq(a,qs[a]-qs[mid]);
		if(ql<=b&&b<=qr)l=mid;
		else r=mid-1;
	}
	if(1<=l)res=min(res,qs[a]-qs[l]);
	return res;
}