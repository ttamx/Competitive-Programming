#include "ancient2.h"
#include<bits/stdc++.h>

using namespace std;

string Solve(int n) {
	vector<bool> ans(n);
	int m = 502;
	vector<int> a(m),b(m);
	a[m-2]=b[m-2]=m-2;
	a[m-1]=b[m-1]=m-1;
	for(int i=0;i<n/2;i++){
		a[i]=m-2;
		b[i]=m-1;
	}
	for(int i=0;i<n/2;i++){
		int res=Query(m,a,b);
		ans[i]=(res==m-1);
		a[i]=b[i]=i+1;
	}
	string s="";
	for(auto x:ans)s.push_back('0'+x);
	return s;
}