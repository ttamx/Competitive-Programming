#include "Annalib.h"
#include<bits/stdc++.h>

using namespace std;

void Anna(int n,long long x,int k,int p[]){
	using ull = uint64_t;
	mt19937_64 rng(0);
	vector<ull> basis(64),way(64);
	vector<int> id(64,-1);
	auto add=[&](ull x,int i){
		ull w=0;
		for(int b=63;b>=0;b--){
			if(x>>b&1){
				if(id[b]==-1){
					basis[b]=x;
					way[b]=w|(1ULL<<b);
					id[b]=i;
					return;
				}
				x^=basis[b];
				w^=way[b];
			}
		}
	};
	vector<bool> ok(n,true);
	for(int i=0;i<k;i++){
		ok[p[i]]=false;
	}
	for(int i=0;i<n;i++){
		ull val=rng();
		if(ok[i]){
			add(val,i);
		}
	}
	vector<int> ans(n);
	ull w=0;
	for(int i=63;i>=0;i--){
		if(x>>i&1){
			x^=basis[i];
			w^=way[i];
		}
	}
	for(int i=63;i>=0;i--){
		if(w>>i&1){
			ans[id[i]]=1;
		}
	}
	for(int i=0;i<n;i++){
		Set(i,ans[i]);
	}
}