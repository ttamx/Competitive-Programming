#include "stick.h"
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int K=1<<19;

int n;
int ans=-1;
vector<int> a;

pair<int,vector<int>> merge(pair<int,vector<int>> a,pair<int,vector<int>> b){
	int mx=max(a.first,b.first);
	int i=0,j=0,idx=0;
	vector<int> ret;
	while(i<a.second.size()&&j<b.second.size()){
		if(a.second[i]>b.second[j]){
			ret.push_back(a.second[i]);
			i++;
		}else{
			ret.push_back(b.second[j]);
			j++;
		}
		if(idx>=2){
			if(ret[idx-2]+ret[idx-1]+ret[idx]<=mx)return {mx,ret};
			if(ret[idx-2]<ret[idx-1]+ret[idx]){
				return {ret[idx-2]+ret[idx-1]+ret[idx],ret};
			}
		}
		idx++;
	}
	while(i<a.second.size()){
		ret.push_back(a.second[i]);
		i++;
		if(idx>=2){
			if(ret[idx-2]+ret[idx-1]+ret[idx]<=mx)return {mx,ret};
			if(ret[idx-2]<ret[idx-1]+ret[idx]){
				return {ret[idx-2]+ret[idx-1]+ret[idx],ret};
			}
		}
		idx++;
	}
	while(j<b.second.size()){
		ret.push_back(b.second[j]);
		j++;
		if(idx>=2){
			if(ret[idx-2]+ret[idx-1]+ret[idx]<=mx)return {mx,ret};
			if(ret[idx-2]<ret[idx-1]+ret[idx]){
				return {ret[idx-2]+ret[idx-1]+ret[idx],ret};
			}
		}
		idx++;
	}
	return {mx,ret};
}

struct segtree{
	pair<int,vector<int>> tree[K];
	void build(int l,int r,int i){
		if(l==r){
			tree[i]={-1,{a[l]}};
			return;
		}
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		tree[i]=merge(tree[i*2],tree[i*2+1]);
	}
	pair<int,vector<int>> query(int l,int r,int i,int x,int y){
		if(r<x||l>y)return {-1,{}};
		if(x<=l&&r<=y)return tree[i];
		int m=(l+r)/2;
		return merge(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
	}
}seg;

void init(int N, std::vector<int> v){
	n=N;
	a=v;
	seg.build(0,n-1,1);
  	return;
}

int max_length(int L,int R){
  	return seg.query(0,n-1,1,L,R).first;
}
