#include "elephants.h"
#include<bits/stdc++.h>

using namespace std;

const int N=150005;
const int K=390;
const int inf=1e9;

int n,L;
int X[N];

struct elephant{
	int id,pos,needed,covered;
	elephant(){}
	elephant(int id,int pos):id(id),pos(pos){}
	bool operator<(const elephant &o)const{
		return pos<o.pos;
	}
}elep[N];

vector<elephant> block[K];
int blockid[N];

void computeblock(int i){
	deque<elephant> dq;
	for(int j=block[i].size()-1;j>=0;j--){
		if(dq.empty()||block[i][j].pos+L>=dq.back().pos){
			block[i][j].needed=1;
			block[i][j].covered=block[i][j].pos+L;
		}else{
			while(dq.size()>1&&dq.end()[-2].pos>block[i][j].pos+L)dq.pop_back();
			block[i][j].needed=dq.back().needed+1;
			block[i][j].covered=dq.back().covered;
		}
		dq.emplace_front(block[i][j]);
	}
}

void build(){
	for(int i=0;i<K;i++)block[i].clear();
	for(int i=0;i<n;i++){
		block[i/K].emplace_back(elep[i]);
		blockid[elep[i].id]=i/K;
	}
	for(int i=0;i<K;i++)computeblock(i);
}

void init(int N, int _L, int _X[]){
	n=N,L=_L;
	for(int i=0;i<n;i++)X[i]=_X[i];
	for(int i=0;i<n;i++)elep[i]=elephant(i,X[i]);
	build();
}

int findblock(int pos){
	int l=0,r=K-1;
	while(l<r){
		int m=(l+r+1)/2;
		if(!block[m].empty()&&block[m][0].pos<=pos)l=m;
		else r=m-1;
	}
	return l;
}

int counter=0;

int update(int i, int y){
	if(counter==K){
		counter=0;
		int idx=0;
		for(int j=0;j<K;j++)for(auto e:block[j])elep[idx++]=e;
		build();
	}
	counter++;
	int id=blockid[i];
	auto it=block[id].begin();
	while(it->id!=i)it++;
	auto tmp=*it;
	block[id].erase(it);
	computeblock(id);
	X[i]=y;
	tmp.pos=y;
	id=findblock(X[i]);
	blockid[i]=id;
	it=block[id].begin();
	while(it!=block[id].end()&&it->pos<=X[i])it++;
	block[id].insert(it,tmp);
	computeblock(id);
	int ans=0;
	int pos=-inf;
	for(int i=0;i<K;i++){
		auto it=upper_bound(block[i].begin(),block[i].end(),elephant(-1,pos));
		if(it==block[i].end())continue;
		ans+=it->needed;
		pos=it->covered;
	}
	return ans;
}