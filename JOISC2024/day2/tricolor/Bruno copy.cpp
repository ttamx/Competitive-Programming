#include "Bruno.h"
#include<bits/stdc++.h>

using namespace std;

namespace {

const int B=16;

int n,l;
vector<int> v;
vector<int> pos;

int encode[81] = {
	2,5,0,0,2,2,7,6,3,
	3,7,6,5,1,7,6,0,1,
	1,6,4,2,4,1,4,1,5,
	5,7,1,2,3,7,4,0,6,
	6,4,0,0,5,4,7,1,2,
	0,2,6,2,1,3,5,3,6,
	3,6,5,6,3,4,1,6,0,
	1,2,4,4,3,5,4,6,3,
	0,4,7,1,7,0,6,5,2,
};

vector<int> DeBrujin(int l){
	vector<int> res;
	int n=1<<(l-1);
	vector<int> ptr(n);
	function<void(int)> dfs=[&](int u){
		for(int i=ptr[u];ptr[u]++<2;i++){
			dfs(((u<<1)&~n)|i);
			res.emplace_back(i);
		}
	};
	dfs(0);
	for(int i=0;i<l-1;i++)res.emplace_back(res[i]);
	return res;
}

}  // namespace

void init(int N, int L) {
	n=N,l=L;
	v=DeBrujin(B);
	pos.resize(1<<B);
	int val=0;
	for(int i=0;i<B-1;i++)val=val*2+v[i];
	int cnt=0;
	for(int i=B-1;i<pos.size();i++){
		val=((val<<1)&((1<<B)-1))|v[i];
		pos[val]=cnt;
		cnt+=2;
	}
}

int bruno(string s){
	cerr << s << "\n";
	if(n==l)return 1;
	vector<int> a(l);
	for(int i=0;i<n;i++){
		if(s[i]=='R')a[i]=0;
		if(s[i]=='G')a[i]=1;
		if(s[i]=='B')a[i]=2;
	}
	int add=0;
	while(add<4){
		bool ok=true;
		for(int i=add;i+3<l;i+=4){
			int val=encode[a[i]*27+a[i+1]*9+a[i+2]*3+a[i+3]];
			cerr << (val&2) << (val&1);
			if(val&4){
				add++;
				ok=false;
				break;
			}
		}
		cerr << "\n";
		if(ok)break;
	}
	assert(add<4);
	cerr << "ADD " << add << "\n";
	int res=0;
	for(int i=add;i+3<l;i+=4){
		int val=encode[a[i]*27+a[i+1]*9+a[i+2]*3+a[i+3]];
		res=res*4+val;
	}
	cerr << pos[res]+1-add << "\n";
	return pos[res]+1-add;
}

