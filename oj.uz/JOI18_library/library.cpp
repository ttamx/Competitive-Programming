#include <bits/stdc++.h>
#include "library.h"

using namespace std;

void Solve(int n){
	vector<int> a(n);
	iota(a.begin(),a.end(),0);
	auto del=[&](int x){
		a.erase(a.begin()+x);
	};
	vector<int> qr(n,1);
	int st=0;
	for(int i=1;i<n;i++){
		qr[i]=0;
		if(Query(qr)==1){
			st=i;
			break;
		}
		qr[i]=1;
	}
	del(st);
	vector<int> ans{st};
	for(int t=1;t<n;t++){
		int l=0,r=a.size()-1;
		while(l<r){
			int m=(l+r)/2;
			qr.assign(n,0);
			for(int i=0;i<=m;i++)qr[a[i]]=1;
			int res=Query(qr);
			qr[ans.back()]=1;
			if(Query(qr)==res)r=m;
			else l=m+1;
		}
		ans.emplace_back(a[l]);
		del(l);
	}
	for(auto &x:ans)x++;
	Answer(ans);
}