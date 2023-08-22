#include "sorting.h"
#include<bits/stdc++.h>

using namespace std;

int n,m;
vector<int> s,x,y;
vector<pair<int,int>> ans;

bool chk(int val,bool gen=false){
	vector<int> id(n),pos(n),pos2(n),tar(n);
	iota(id.begin(),id.end(),0);
	iota(tar.begin(),tar.end(),0);
	iota(pos2.begin(),pos2.end(),0);
	for(int i=0;i<val;i++)swap(tar[x[i]],tar[y[i]]);
	for(int i=0;i<n;i++)pos[s[i]]=i;
	auto seq=s;
	auto doswap=[&](int u,int v){
		swap(seq[u],seq[v]);
		swap(pos[seq[u]],pos[seq[v]]);
		swap(id[u],id[v]);
		swap(pos2[id[u]],pos2[id[v]]);
	};
	int cnt=0;
	for(int i=0;i<n;i++){
		if(id[pos[i]]!=tar[i]){
			doswap(x[cnt],y[cnt]);
			int u=pos[i],v=pos2[tar[i]];
			if(gen)ans.emplace_back(u,v);
			swap(seq[u],seq[v]);
			swap(pos[seq[u]],pos[seq[v]]);
			cnt++;
		}
	}
	return cnt<=val;
}

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
	n=N,m=M;
	for(int i=0;i<N;i++){
		s.emplace_back(S[i]);
		x.emplace_back(X[i]);
		y.emplace_back(Y[i]);
	}
	int l=0,r=n-1;
	while(l<r){
		int mid=(l+r)/2;
		auto seq=s;
		if(chk(mid))r=mid;
		else l=mid+1;
	}
	chk(l,true);
	while(ans.size()<l)ans.emplace_back(0,0);
	for(int i=0;i<l;i++)tie(P[i],Q[i])=ans[i];
	return l;
}