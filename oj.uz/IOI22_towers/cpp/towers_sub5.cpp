#include "towers.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int LG=17;
const int inf=2e9;

int n;
int h[N],spmx[LG][N],spmn[LG][N];
vector<int> vec;

int rmxq(int l,int r){
	int k=31-__builtin_clz(r-l+1);
	return max(spmx[k][l],spmx[k][r-(1<<k)+1]);
}

int rmnq(int l,int r){
	int k=31-__builtin_clz(r-l+1);
	return min(spmn[k][l],spmn[k][r-(1<<k)+1]);
}

void init(int N,vector<int> H){
	n=N;
	for(int i=1;i<=n;i++)h[i]=H[i-1];
	h[0]=h[n+1]=inf;
	for(int i=0;i<=n+1;i++)spmx[0][i]=spmn[0][i]=h[i];
	for(int i=1;i<LG;i++){
		for(int j=0;j+(1<<i)-1<=n+1;j++){
			spmx[i][j]=max(spmx[i-1][j],spmx[i-1][j+(1<<(i-1))]);
			spmn[i][j]=min(spmn[i-1][j],spmn[i-1][j+(1<<(i-1))]);
		}
	}
	auto lb=[&](int id){
		int l=0,r=id-1;
		while(l<r){
			int m=(l+r+1)/2;
			if(rmnq(m,id)<h[id])l=m;
			else r=m-1;
		}
		return l;
	};
	auto ub=[&](int id){
		int l=id+1,r=n+1;
		while(l<r){
			int m=(l+r)/2;
			if(rmnq(id,m)<h[id])r=m;
			else l=m+1;
		}
		return l;
	};
	for(int i=1;i<=n;i++){
		int l=lb(i),r=ub(i);
		int d=min(rmxq(l,i),rmxq(i,r))-h[i];
		vec.emplace_back(d);
	}
	sort(vec.begin(),vec.end());
}

int max_towers(int L,int R,int D){
	L++,R++;
	return n-(lower_bound(vec.begin(),vec.end(),D)-vec.begin());
}