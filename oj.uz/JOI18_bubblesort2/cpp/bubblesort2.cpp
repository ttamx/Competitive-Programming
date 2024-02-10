#include "bubblesort2.h"
#include<bits/stdc++.h>

using namespace std;

using pi = pair<int,int>;

struct Segtree{
	int n;
	vector<int> t,lz;
	Segtree(int _n){
		n=_n;
		int s=4<<(31-__builtin_clz(n));
		t.assign(s,0);
		lz.assign(s,0);
	}
	void push(int l,int r,int i){
		t[i]+=lz[i];
		if(l<r){
			lz[i*2]+=lz[i];
			lz[i*2+1]+=lz[i];
		}
		lz[i]=0;
	}
	void update(int l,int r,int i,int x,int y,int v){
		push(l,r,i);
		if(y<l||r<x)return;
		if(x<=l&&r<=y)return lz[i]=v,push(l,r,i);
		int m=(l+r)/2;
		update(l,m,i*2,x,y,v);
		update(m+1,r,i*2+1,x,y,v);
		t[i]=max(t[i*2],t[i*2+1]);
	}
	void update(int x,int y,int v){
		update(0,n-1,1,x,y,v);
	}
};

vector<int> countScans(vector<int> a,vector<int> x,vector<int> v){
	int n=a.size();
	int q=x.size();
	vector<int> ans(q);
	vector<pi> vec;
	for(int i=0;i<n;i++)vec.emplace_back(a[i],i);
	for(int i=0;i<q;i++)vec.emplace_back(v[i],x[i]);
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	for(int i=0;i<n;i++)a[i]=lower_bound(vec.begin(),vec.end(),pi(a[i],i))-vec.begin();
	for(int i=0;i<q;i++)v[i]=lower_bound(vec.begin(),vec.end(),pi(v[i],x[i]))-vec.begin();
	Segtree s(n+q);
	auto upd=[&](int i,int v){
		s.update(a[i],a[i],i*v);
		s.update(a[i]+1,n+q,-v);
	};
	for(int i=0;i<n;i++)upd(i,1);
	for(int i=0;i<q;i++){
		upd(x[i],-1);
		a[x[i]]=v[i];
		upd(x[i],1);
		ans[i]=s.t[1];
	}
	return ans;
}