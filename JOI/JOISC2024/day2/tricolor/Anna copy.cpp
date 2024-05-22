#include "Anna.h"
#include<bits/stdc++.h>

using namespace std;

namespace {

int encode[81] = {
	2,5,0,0,2,2,7,6,3,
	3,7,6,5,1,7,6,0,1,
	1,6,4,2,4,1,4,1,5,
	5,7,1,2,3,7,4,0,6,
	6,4,0,0,5,4,7,1,2,
	0,2,6,2,1,3,5,3,6,
	3,6,5,6,3,4,1,6,0,
	1,2,4,4,3,5,4,6,3,
	0,4,7,1,7,0,6,5,2
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

}

pair<string,int> anna(int n,string s) {
	vector<int> a(n+4);
	for(int i=0;i<n;i++){
		if(s[i]=='R')a[i]=0;
		if(s[i]=='G')a[i]=1;
		if(s[i]=='B')a[i]=2;
	}
	int L=16;
	auto v=DeBrujin(L);
	auto get=[&](int val,int id){
		for(int i=0;i<3;i++)if(i!=a[id]){
			for(int j=0;j<3;j++)if(j!=a[id+1]){
				for(int k=0;k<3;k++)if(k!=a[id+2]){
					for(int l=0;l<3;l++)if(l!=a[id+3]){
						if(encode[i*27+j*9+k*3+l]==val){
							return vector<int>{i,j,k,l};
						}
					}
				}
			}
		}
		assert(false);
		return vector<int>();
	};
	string ans="";
	for(int i=0,j=0;i<n;i+=4,j+=2){
		auto tmp=get(v[j]*2+v[j+1],i);
		for(auto x:tmp)ans.push_back("RGB"[x]);
	}
	ans.resize(n);
	cerr << ans << "\n";
	return make_pair(ans,min(n,(L+1)/2*4+3));
}