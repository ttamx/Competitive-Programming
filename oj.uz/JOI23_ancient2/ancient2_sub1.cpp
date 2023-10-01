#include "ancient2.h"
#include<bits/stdc++.h>

using namespace std;

string Solve(int n) {
	string ans(n,'0');
	int m = n+2;
	vector<int> a(m),b(m);
	a[n]=b[n]=n;
	a[n+1]=b[n+1]=n+1;
	for(int i=0;i<n;i++){
		a[i]=n;
		b[i]=n+1;
	}
	for(int i=0;i<n;i++){
		int res=Query(m,a,b);
		ans[i]=res-n+'0';
		a[i]=b[i]=i+1;
	}
	return ans;
}