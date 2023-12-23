#include "towers.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int LG=17;

int n;
int h[N],sp[LG][N];

int rmq(int l,int r){
	int k=31-__builtin_clz(r-l+1);
	return max(sp[k][l],sp[k][r-(1<<k)+1]);
}

void init(int N,vector<int> H){
	n=N;
	for(int i=1;i<=n;i++)sp[0][i]=h[i]=H[i-1];
	for(int i=1;i<LG;i++){
		for(int j=1;j+(1<<i)-1<=n;j++){
			sp[i][j]=max(sp[i-1][j],sp[i-1][j+(1<<(i-1))]);
		}
	}
}

int max_towers(int L,int R,int D){
	L++,R++;
	vector<pair<int,int>> vec;
	for(int i=L;i<=R;i++)vec.emplace_back(h[i],i);
	sort(vec.begin(),vec.end());
	set<int> ans;
	auto lb=[&](int id){
		int l=L-1,r=id-1;
		while(l<r){
			int m=(l+r+1)/2;
			if(rmq(m,id)>=h[id]+D)l=m;
			else r=m-1;
		}
		return l;
	};
	auto ub=[&](int id){
		int l=id+1,r=R+1;
		while(l<r){
			int m=(l+r)/2;
			if(rmq(id,m)>=h[id]+D)r=m;
			else l=m+1;
		}
		return l;
	};
	for(auto [hei,id]:vec){
		int l=lb(id),r=ub(id);
		auto it=ans.lower_bound(l);
		if(it==ans.end()||*it>r)ans.emplace(id);
	}
	return ans.size();
}