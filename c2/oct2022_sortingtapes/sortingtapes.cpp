#include<bits/stdc++.h>
#include "sortingtapes.h"

using namespace std;

typedef tuple<int,int,int> t3;
typedef tuple<int,int,int,int> t4;

struct mosalgo{
	int n,k;
	bool revl,revr;
	vector<vector<t3>> queries;
	deque<bool> ans;
	void init(int _n){
		n=_n;
		k=ceil(sqrt(n));
		queries.resize(k);
	}
	void push(int l,int r){
		queries[l/k].emplace_back(r,l,(int)ans.size());
		ans.emplace_back(0);
	}
	bool pop(){
		bool res=ans.front();
		ans.pop_front();
		return res;
	}
	void compute(){
		if(revl)reverse(queries.begin(),queries.end());
		revl^=true;
		for(auto &block:queries){
			sort(block.begin(),block.end());
			if(revr)reverse(block.begin(),block.end());
			revr^=true;
			for(auto &[r,l,i]:block)ans[i]=compare(l,r);
			block.clear();
		}
	}
}qr;

vector<int> sort_tapes(int n, vector<int> a, vector<int> b) {
	vector<int> ans(2*n,-1);
	qr.init(n);
	vector<t4> q;
	q.emplace_back(0,n-1,0,n-1);
	while(!q.empty()){
		vector<t4> q2;
		for(auto [al,ar,bl,br]:q){
			if(al>ar)continue;
			int am=(al+ar)/2;
			for(int i=bl;i<=br;i++)qr.push(a[am],b[i]);
		}
		qr.compute();
		for(auto [al,ar,bl,br]:q){
			if(al>ar)continue;
			int am=(al+ar)/2;
			int bm=br+1;
			for(int i=bl;i<=br;i++)if(qr.pop())bm=min(bm,i);
			ans[am+bm]=a[am];
			q2.emplace_back(al,am-1,bl,bm-1);
			q2.emplace_back(am+1,ar,bm,br);
		}
		swap(q,q2);
	}
	int id=0;
	for(auto &x:ans)if(x<0)x=b[id++];
	return ans;
}